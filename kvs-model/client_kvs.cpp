// C++ program to illustrate the client application in the
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 44000
#define MAXLINE 4096
#define MAXPAYLOAD 16 // Size of value in Bytes

#define GIG 1000000000
#define CPG 3.4 // Cycles per GHz -- Adjust to your computer
#define SIZES 1 // MAKE 7
#define ITERS 2

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
    uint32_t key;
} __attribute__((packed)) MemCD_Get_Req_t;

typedef struct
{
    MemCD_HDR_t header;
    uint32_t extras_flags;
    uint32_t extras_expiration;
    uint32_t key; // Fixed key size for this implementation.
    uint8_t value[MAXPAYLOAD];
} __attribute__((packed)) MemCD_Set_Req_t;

void sendGetRequest(int clientSocket)
{
    // populate packet metadata
    MemCD_Get_Req_t *g1;
    g1 = (MemCD_Get_Req_t *)malloc(sizeof(MemCD_Get_Req_t));
    g1->header.Magic = 0x80;
    g1->header.Opcode = 0x00;
    g1->header.KeyLength = 4;
    g1->header.ExtrasLength = 0;
    g1->header.DataType = 0;
    g1->header.vbucketID = 0;
    g1->header.BodyLength = 4; // key
    g1->header.Opaque = 0;
    g1->header.CAS = 0;

    // populate packet data
    g1->key = 1;

    // sending data
    send(clientSocket, g1, sizeof(MemCD_Get_Req_t), 0);
}

void sendSetRequest(int clientServer)
{
    MemCD_Set_Req_t *s1;
    s1 = (MemCD_Set_Req_t *)malloc(sizeof(MemCD_Set_Req_t));
    s1->header.Magic = 0x80;
    s1->header.Opcode = 0x01;
    s1->header.KeyLength = 4;
    s1->header.ExtrasLength = 8;
    s1->header.DataType = 0;
    s1->header.vbucketID = 0;
    s1->header.BodyLength = 28; // key + extra + value = 4+8+16
    s1->header.Opaque = 0;
    s1->header.CAS = 0;
    s1->extras_flags = 0;
    s1->extras_expiration = 0;
    s1->key = 1;

    for (int i = 0; i < MAXPAYLOAD; i++)
    {
        s1->value[i] = rand();
    }
}

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // sending connection request
    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    sendGetRequest(clientSocket);
    // closing socket
    close(clientSocket);

    return 0;
}