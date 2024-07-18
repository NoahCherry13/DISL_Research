all: server client

server: server_perf.cpp
	g++ server_perf.cpp -o serv

client: client_perf.cpp
	g++ client_perf.cpp -o cli

packet_store: packet_store.cpp -o packet_store

dictionary: dictionary.cpp -o dictionary

clean:
	rm cli serv dictionary packet_store
