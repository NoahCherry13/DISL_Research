all: server client

server: server_kvs.cpp
	g++ server_kvs.cpp -o server

client: client_kvs.cpp
	g++ client_kvs.cpp -o client

run:
	./server &
	./client

packet_store: packet_store.cpp -o packet_store

dictionary: dictionary.cpp -o dictionary

clean:
	rm client server dictionary packet_store
