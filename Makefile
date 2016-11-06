CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=gnu99

SERVER = multi
CLIENT = client

.PHONY: all clean
all: $(SERVER) $(CLIENT)
clean:
	-rm $(SERVER) $(CLIENT) $(SERVER).o $(CLIENT).o

$(SERVER): $(SERVER).o
	$(CC) $(CFLAGS) $^ -o $@
$(CLIENT): $(CLIENT).o
	$(CC) $(CFLAGS) $^ -o $@

