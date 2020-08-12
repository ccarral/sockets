
all: server client

server : server.c 
	gcc -I . server.c -o server

client: client.c
	gcc -I . client.c -o client
