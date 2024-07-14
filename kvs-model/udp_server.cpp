#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h> 
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

// variables
unordered_map<uint32_t, uint8_t *> kvs;
char *buffer;

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

// //helper functions
void rx_get(MemCD_Set_Req_t *rg1, int clientSocket, sockaddr_in *caddr_ptr, socklen_t *sz_ptr)
{
     // fetch value and populate response data
     MemCD_Resp_t *tx1 = (MemCD_Resp_t *)malloc(sizeof(MemCD_Resp_t));
     uint32_t key = ((MemCD_Get_Req_t *)rg1)->key;
     for (int i = 0; i < MAXPAYLOAD; i++)
     {
          tx1->Data[i] = kvs[key][i];
     }

     // Populate Response Metadata
     tx1->Magic = 0;
     tx1->Opcode = 0x02;
     tx1->KeyLength = 0x0;
     tx1->ExtrasLength = 0x0;
     tx1->DataType = 0x0;
     tx1->Status = 0x0;
     tx1->BodyLength = 0x0;
     tx1->Opaque = 0x0;
     tx1->CAS = 0x0;

     // Send Response Packet
     sendto(clientSocket, tx1, sizeof(MemCD_Resp_t), MSG_CONFIRM,
            (const struct sockaddr *)caddr_ptr, *sz_ptr);
     free((MemCD_Resp_t *)tx1);
     // free(rg1);
}

void rx_set(MemCD_Set_Req_t *rs1)
{
     uint32_t key;
     uint8_t *value;

     key = rs1->key;
     if (kvs.count(key) <= 0)
     {
          value = (uint8_t *)malloc(MAXPAYLOAD * sizeof(uint8_t));
          for (int i = 0; i < MAXPAYLOAD; i++)
          {
               value[i] = rs1->value[i];
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

void process_packet(int clientSocket, sockaddr_in *caddr_ptr, socklen_t *sz_ptr)
{
     printf("Waiting to get something...\n");
     MemCD_Set_Req_t *rx1 = (MemCD_Set_Req_t *)malloc(sizeof(MemCD_Set_Req_t));
     
     int bytes_rcv = recvfrom(clientSocket, rx1, MAXLINE, MSG_WAITALL,
                              (struct sockaddr *)caddr_ptr, sz_ptr);
     printf("Got Something!\n");
     // determine opcode
     if(rx1->header.Opcode == 0x00){
          rx_get(rx1, clientSocket, caddr_ptr, sz_ptr);
     }
     else if (rx1->header.Opcode == 0x01)
     {
          rx_set(rx1);
     }
}

int main()
{
     // allocating buffer
     buffer = (char *)malloc(MAXLINE);
     // creating socket
     int clientSocket;
     if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
     {
          perror("socket creation failed");
          exit(EXIT_FAILURE);
     }
     // specifying the address
     sockaddr_in saddr, caddr;
     saddr.sin_family = AF_INET;
     saddr.sin_port = htons(PORT);
     saddr.sin_addr.s_addr = inet_addr(IPADDR);

     socklen_t caddr_sz = sizeof(caddr);
     socklen_t saddr_sz = sizeof(saddr);
     memset(&saddr, 0, saddr_sz);
     memset(&caddr, 0, caddr_sz);

     // binding socket.
     if (bind(clientSocket, (const struct sockaddr *)&saddr,
              sizeof(saddr)) < 0)
     {
          perror("bind failed");
          exit(EXIT_FAILURE);
     }
     printf("before process\n");
     process_packet(clientSocket, &caddr, &caddr_sz);

     // close socket.
     printf("closing the socket\n");

     return 0;
}
