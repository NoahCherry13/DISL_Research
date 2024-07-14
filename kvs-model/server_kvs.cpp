#include <cstring>
#include <iostream>
#include <arpa/inet.h> 
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
#define IPADDR "127.0.0.1"

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
unordered_map<uint32_t, uint8_t *> kvs;
MemCD_Get_Req_t *rg1;
MemCD_Set_Req_t *rs1;

// //helper functions
void rx_get(MemCD_Get_Req_t *rg1, int clientSocket)
{

     // MemCD_Resp_t *tx1 = (MemCD_Resp_t *)malloc(sizeof(MemCD_Resp_t));
     // uint32_t key = rg1->key;
     // printf("Get Key: %x\n", key);
     // memcpy(tx1->Data, "Hello", 16);
     // tx1->Magic = 0;
     // tx1->Opcode = 0x02;
     // tx1->KeyLength = 0x0;
     // tx1->ExtrasLength = 0x0;
     // tx1->DataType = 0x0;
     // tx1->Status = 0x0;
     // tx1->BodyLength = 0x0;
     // tx1->Opaque = 0x0;
     // tx1->CAS = 0x0;
     // send(clientSocket, tx1, sizeof(MemCD_Resp_t), 0);
     // printf("Sent Packet\n");
}

void rx_set(MemCD_Set_Req_t *rs1)
{
     // // handle set request
     // uint32_t key = rs1->key;
     // uint8_t *value;
     // printf("\n)");

     // if (kvs.count(key) <= 0)
     // {

     //      value = (uint8_t *)malloc(MAXPAYLOAD * sizeof(uint8_t));
     //      printf("after malloc\n");
     //      for (int i = 0; i < MAXPAYLOAD; i++)
     //      {
     //           value[i] = rs1->value[i];
     //      }

     //      kvs.insert(make_pair(key, value));
     //      for (int i = 0; i < MAXPAYLOAD; i++)
     //      {
     //           printf("%c", rs1->value[i]);
     //      }
     // }
     // else
     // {
     //      // kvs[rs1->key] = rs1->value;
     // }
}

void process_packet(int clientSocket)
{
     MemCD_Set_Req_t *rx1 = (MemCD_Set_Req_t *)malloc(sizeof(MemCD_Set_Req_t));
     // recieving data
     recv(clientSocket, rx1, sizeof(MemCD_Set_Req_t), 0);
     if (rx1->header.Opcode == 0x00)
     {
          // rx_get((MemCD_Get_Req_t *)rx1, clientSocket);
          MemCD_Resp_t *tx1 = (MemCD_Resp_t *)malloc(sizeof(MemCD_Resp_t));
          uint32_t key = ((MemCD_Get_Req_t *)rx1)->key;
          for (int i = 0; i < MAXPAYLOAD; i++)
          {
               tx1->Data[i] = 'N';
          }
          tx1->Magic = 0;
          tx1->Opcode = 0x02;
          tx1->KeyLength = 0x0;
          tx1->ExtrasLength = 0x0;
          tx1->DataType = 0x0;
          tx1->Status = 0x0;
          tx1->BodyLength = 0x0;
          tx1->Opaque = 0x0;
          tx1->CAS = 0x0;
          send(clientSocket, tx1, sizeof(MemCD_Resp_t), 0);
          free(tx1);
          free(rx1);
     }
     else if (rx1->header.Opcode == 0x01)
     {
          // rx_set((MemCD_Set_Req_t *)rx1);
          uint32_t key = rx1->key;
          uint8_t *value;

          if (kvs.count(key) <= 0)
          {

               value = (uint8_t *)malloc(MAXPAYLOAD * sizeof(uint8_t));
               for (int i = 0; i < MAXPAYLOAD; i++)
               {
                    value[i] = rx1->value[i];
               }
               kvs.insert(make_pair(key, value));
          }
          else
          {
               for (int i = 0; i < MAXPAYLOAD; i++)
               {
                    kvs[key][i] = rs1->value[i];
               }
               
          }
     }
}

int main()
{
     // creating socket
     int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

     // specifying the address
     sockaddr_in serverAddress;
     serverAddress.sin_family = AF_INET;
     serverAddress.sin_port = htons(PORT);
     serverAddress.sin_addr.s_addr = inet_addr(IPADDR);

     // binding socket.
     bind(serverSocket, (struct sockaddr *)&serverAddress,
          sizeof(serverAddress));

     // listening to the assigned socket
     listen(serverSocket, 5);
     // accepting connection request
     int clientSocket = accept(serverSocket, nullptr, nullptr);
     while(1){ process_packet(clientSocket);}
     //process_packet(clientSocket);
     // closing the socket.
     printf("closing the socket\n");
     close(serverSocket);

     return 0;
}