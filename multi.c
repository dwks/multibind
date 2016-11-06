#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 3088
#define STRING(x) #x
#define STRING2(x) STRING(x)

#define BEGIN_FORKING 2
#define MAX_GENERATIONS 3
#define MAX_RUNTIME 10

void die(const char *func) {
    perror(func);
    exit(1);
}

int generation = 0;
int message(const char *format, ...) {
    va_list arg;

    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[gen %d pid %d] %s\n",
        generation, (int)getpid(), format);

    va_start(arg, format);
    int r = vfprintf(stderr, buffer, arg);
    va_end(arg);
    return r;
}

time_t launch;
int has_forked = 0;
void do_fork(void) {
    if(has_forked) return;
    if(generation > MAX_GENERATIONS) return;

    pid_t pid = fork();
    if(pid == 0) {  /* child */
        generation ++;
        alarm(1);
        launch = time(NULL);
        message("launched new multibind process");
    }
    else {
        has_forked = 1;
    }
}

int open_socket(void) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if(getaddrinfo(NULL, STRING2(PORT), &hints, &res) != 0) {
        die("getaddrinfo");
    }

    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(fd < 0) {
        die("socket");
    }

    int optval = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof optval) != 0) {
        die("setsockopt");
    }

    if(bind(fd, res->ai_addr, res->ai_addrlen) != 0) {
        die("bind");
    }

    if(listen(fd, 10) != 0) {
        die("listen");
    }

    return fd;
}

int should_exit = 0;
void sigalrm_handler(int sig) {
    time_t now = time(NULL);
    if(now >= launch + MAX_RUNTIME) {
        should_exit = 1;
    }
    else if(now >= launch + BEGIN_FORKING && !has_forked) {
        do_fork();
    }

    if(!should_exit) {
        alarm(1);
    }
}

int main(int argc, char *argv[]) {
    launch = time(NULL);
    message("starting multibind process");

    struct sigaction act;
    act.sa_handler = &sigalrm_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);
    alarm(1);

    int fd = open_socket();

    while(!should_exit) {
        struct sockaddr_storage client;
        socklen_t client_size = sizeof client;
        int cfd = accept(fd, (struct sockaddr *)&client, &client_size);

        uint32_t data = (uint32_t)generation;
        write(cfd, &data, sizeof data);

        close(cfd);

        //char buffer[256];
        //fgets(buffer, sizeof buffer, stdin);
    }

    message("exiting multibind process");
    return 0;
}
