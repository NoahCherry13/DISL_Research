all: server client kvs_perf

server: server_kvs.cpp
	g++ server_kvs.cpp -o server

client: client_kvs.cpp
	g++ client_kvs.cpp -o client

kvs_perf: kvs_perf.c
	g++ kvs_perf.c -o kvs_perf

run:
	./server &
	./client

packet_store: packet_store.cpp -o packet_store

dictionary: dictionary.cpp -o dictionary

clean:
	rm client server dictionary packet_store kvs_perf
