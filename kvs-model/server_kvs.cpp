#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <unordered_map>

using namespace std;

#define PORT 44000
#define MAXLINE 4096
#define MAXPAYLOAD 16 // Size of value in Bytes

#define GIG 1000000000
#define CPG 3.4 // Cycles per GHz -- Adjust to your computer
#define SIZES 1 // MAKE 7
#define ITERS 2

// structures for memcopyd packets (simplified)
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

typedef struct
{
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

typedef struct
{
     MemCD_HDR_t header;
     uint32_t extras_flags;
     uint32_t extras_expiration;
     uint32_t key; // Fixed key size for this implementation.
     uint8_t value[MAXPAYLOAD];
} __attribute__((packed)) MemCD_Set_Req_t;

typedef struct
{
     MemCD_HDR_t header;
     uint32_t key;
} __attribute__((packed)) MemCD_Get_Req_t;

// variables
unordered_map<uint32_t, uint8_t*> kvs;
MemCD_Get_Req_t *rg1;
MemCD_Set_Req_t *rs1;
MemCD_HDR_t *rx1;
MemCD_Resp_t *tx1;

// //helper functions
// void process_packet(MemCD_HDR_t *rx1){

// }

int main()
{
     // creating socket
     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

     rx1 = (MemCD_HDR_t *)malloc(sizeof(MemCD_HDR_t));
     tx1 = (MemCD_Resp_t *)malloc(sizeof(MemCD_Resp_t));
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
     recv(clientSocket, rx1, sizeof(MemCD_HDR_t), 0);
     if (rx1->Opcode == 0x00)
     {
          // handle get request
          rg1 = (MemCD_Get_Req_t*)rx1;
          
     }
     else if (rx1->Opcode == 0x01)
     {
          // handle set request
          rs1 = (MemCD_Set_Req_t*)rx1;
          uint32_t key = (uint32_t)rs1->key;
          uint8_t *value = rs1->value;
          if (kvs.count(key) <= 0){
               kvs.insert(make_pair(key, value));
               printf("Inserted New KV pair:\nkey: %x\nval: %hhn\n", key, value);
          }else{
               //kvs[rs1->key] = rs1->value;
               printf("set\n");
          }
     }
     // closing the socket.
     close(serverSocket);

     return 0;
}