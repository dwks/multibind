#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 3088
#define STRING(x) #x
#define STRING2(x) STRING(x)

void die(const char *func) {
    perror(func);
    exit(1);
}

int message(const char *format, ...) {
    va_list arg;

    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[client] %s\n", format);

    va_start(arg, format);
    int r = vfprintf(stderr, buffer, arg);
    va_end(arg);
    return r;
}

struct addrinfo *open_socket(int *fd_ptr) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo("localhost", STRING2(PORT), &hints, &res) != 0) {
        die("getaddrinfo");
    }

    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(fd < 0) {
        die("socket");
    }

    *fd_ptr = fd;
    return res;
}

int main(int argc, char *argv[]) {
    message("starting client");
    for(;;) {
        int fd = -1;
        struct addrinfo *res = open_socket(&fd);
        if(connect(fd, res->ai_addr, res->ai_addrlen) != 0) {
            die("connect");
        }

        uint32_t data;
        read(fd, &data, sizeof data);

        message("read from server generation %d", (int)data);

        close(fd);

        system("/bin/sleep 0.2");
    }

    message("exiting client");
    return 0;
}
