all: server client

server: server_kvs.cpp
	g++ server_kvs.cpp -o server

client: client_kvs.cpp
	g++ client_kvs.cpp -o client

clean:
	rm client server
