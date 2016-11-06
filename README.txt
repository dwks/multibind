This project tests whether multiple servers can listen on the same port.

There are two modes:

1) ./test.sh launches multiple servers each of which listen using the
   SO_REUSEPORT option (man 7 socket), allowing the kernel to deliver
   connections to multiple servers fairly.

2) ./multi forks itself to get new processes listening on the same
   sockets. This works with or without SO_REUSEPORT.

Tests: try "./test.sh & ./client" or "./multi & ./client".

-- dwk
