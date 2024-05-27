CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lpthread

# Define targets for both the client and the server
all: client server

# Client binary
client: client.o client_Menu.o authentication.o
	$(CC) $^ $(LDFLAGS) -o client

# Server binary
server: server.o admin.o authentication.o book_management.o borrower.o client_Menu.o librarian.o
	$(CC) $^ $(LDFLAGS) -o server

# Generic rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target for removing built files
clean:
	rm -f *.o client server

# Phony targets ensure make doesn't confuse them with files of the same name
.PHONY: all clean
