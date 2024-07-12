#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <unordered_map>

using namespace std;

#define PORT     44000
#define MAXLINE 4096
#define MAXPAYLOAD 16 // Size of value in Bytes

#define GIG 1000000000
#define CPG 3.4           // Cycles per GHz -- Adjust to your computer
#define SIZES 1           // MAKE 7
#define ITERS 2

//structures for memcopyd packets (simplified)
typedef struct
{
     uint8_t Magic;
     uint8_t Opcode;
     uint16_t KeyLength;
     uint8_t ExtrasLength;
     uint8_t DataType;
     uint16_t vbucketID;
     uint32_t BodyLength;
     uint32_t Opaque;
     uint64_t CAS;
} MemCD_HDR_t;

typedef struct {
  uint8_t Magic;
  uint8_t Opcode;
  uint16_t KeyLength;
  uint8_t ExtrasLength;
  uint8_t DataType;
  uint16_t Status;
  uint32_t BodyLength;
  uint32_t Opaque;
  uint64_t CAS;
  uint8_t Data[MAXPAYLOAD];
} MemCD_Resp_t;

typedef struct{
    MemCD_HDR_t header;
    uint32_t key;
} __attribute__((packed)) MemCD_Get_Req_t;


// variables
unordered_map<int, string> kvs;

int main()
{
     // creating socket
     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

     // specifying the address
     sockaddr_in serverAddress;
     serverAddress.sin_family = AF_INET;
     serverAddress.sin_port = htons(8080);
     serverAddress.sin_addr.s_addr = INADDR_ANY;

     // binding socket.
     bind(serverSocket, (struct sockaddr *)&serverAddress,
          sizeof(serverAddress));

     // listening to the assigned socket
     listen(serverSocket, 5);

     // accepting connection request
     int clientSocket = accept(serverSocket, nullptr, nullptr);

     // recieving data
     // char buffer[1024] = {0};
     spkt_t buffer;
     recv(clientSocket, &buffer, sizeof(buffer), 0);
     printf("got message...\n");
     cout << "Message from client: " << buffer.val << endl;

     // closing the socket.
     close(serverSocket);

     return 0;
}