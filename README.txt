This project tests whether multiple servers can listen on the same port.

There are two modes:

1) ./test.sh launches multiple servers each of which listen using the
   SO_REUSEPORT option (man 7 socket), allowing the kernel to deliver
   connections to multiple servers fairly.

2) ./multi forks itself to get new processes listening on the same
   sockets. This works with or without SO_REUSEPORT.

Tests: try "./test.sh & ./client" or "./multi & ./client". Example run:

$ ./test.sh & ./client
[1] 7568
[gen 0 pid 7570] starting multibind process
[client] starting client
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[gen 1 pid 7592] starting multibind process
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 1
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[gen 2 pid 7614] starting multibind process
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 2
[client] read from server generation 0
[client] read from server generation 2
[client] read from server generation 2
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 1
[client] read from server generation 1
[gen 3 pid 7636] starting multibind process
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 2
[client] read from server generation 0
[client] read from server generation 1
[client] read from server generation 2
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 0
[gen 4 pid 7658] starting multibind process
[client] read from server generation 0
[client] read from server generation 0
[client] read from server generation 4
[client] read from server generation 0
[client] read from server generation 1
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 1
[client] read from server generation 0
[client] read from server generation 3
[gen 0 pid 7570] exiting multibind process
[client] read from server generation 4
[client] read from server generation 2
[client] read from server generation 3
[client] read from server generation 2
[client] read from server generation 4
[client] read from server generation 1
[client] read from server generation 1
[client] read from server generation 2
[client] read from server generation 3
[client] read from server generation 1
[gen 1 pid 7592] exiting multibind process
[client] read from server generation 3
[client] read from server generation 4
[client] read from server generation 2
[client] read from server generation 2
[client] read from server generation 3
[client] read from server generation 3
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 3
[client] read from server generation 4
[gen 2 pid 7614] exiting multibind process
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 3
[client] read from server generation 3
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 3
[client] read from server generation 3
[gen 3 pid 7636] exiting multibind process
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[client] read from server generation 4
[gen 4 pid 7658] exiting multibind process
connect: Connection refused
[1]+  Done                    ./test.sh


-- dwk
