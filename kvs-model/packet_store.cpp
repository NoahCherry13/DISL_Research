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

int main()
{
    unordered_map<uint32_t, uint8_t *> kvs;
    MemCD_Set_Req_t *s1;
    uint32_t key;
    uint8_t *value;

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
    s1->key = 0x00000001;

    key = s1->key;
    for (int i = 0; i < MAXPAYLOAD; i++)
    {
        s1->value[i] = (uint8_t)(rand() % 256);
        printf("%x, %d\n", s1->value[i], i);
    }

    if (kvs.count(key) <= 0)
    {

        value = (uint8_t *)malloc(MAXPAYLOAD * sizeof(uint8_t));
        printf("after malloc\n");
        for (int i = 0; i < MAXPAYLOAD; i++)
        {
            value[i] = s1->value[i];
        }

        kvs.insert(make_pair(key, value));
        for (int i = 0; i < MAXPAYLOAD; i++)
        {
            printf("%x", kvs[key][i]);
        }
    }
    else
    {
        // kvs[rs1->key] = rs1->value;
    }

    return 0;
}