#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
#include <time.h>
#include <math.h>
#include <unordered_map>

#define PORT	 44000
#define MAXLINE 4096
#define MAXPAYLOAD 32 // Size of value in Bytes


using namespace std;

typedef struct {
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
	MemCD_HDR_t header;
	uint32_t key; // Fixed key size for this implementation.
} __attribute__((packed)) MemCD_Get_Req_t;


typedef struct {
	MemCD_HDR_t header;
	uint32_t extras_flags;
	uint32_t extras_expiration;
	uint32_t key; // Fixed key size for this implementation.
	uint8_t value[MAXPAYLOAD];
} __attribute__((packed)) MemCD_Set_Req_t;

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
} MemCD_GetResp_t;

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
} MemCD_SetResp_t;

int main(int argc, char *argv[])
{


	int sockfd_send, sockfd_recv; 
	void *buffer; 
	struct sockaddr_in servaddr, cliaddr;
	MemCD_SetResp_t    *rs1;
	MemCD_GetResp_t    *rg1;
	MemCD_HDR_t        *hdr;
	int n;
	socklen_t len; 
	unordered_map<uint32_t, uint8_t *> kvs;

	rs1 = (MemCD_SetResp_t*) malloc(sizeof(MemCD_SetResp_t));
	rg1 = (MemCD_GetResp_t*) malloc(sizeof(MemCD_GetResp_t));

	rg1->Magic        = 0x81;
	rg1->Opcode       = 0x00;
	rg1->KeyLength    = 4;
	rg1->ExtrasLength = 0;
	rg1->DataType     = 0;
	rg1->Status       = 0;
	rg1->BodyLength   = MAXPAYLOAD; // value
	rg1->Opaque       = 0;
	rg1->CAS          = 0;
	for(int i=0; i<MAXPAYLOAD; i++){ // Initialize with a fixed data value.
		rg1->Data[i] = i;
	}


	rs1->Magic        = 0x81;
	rs1->Opcode       = 0x01;
	rs1->KeyLength    = 4;
	rs1->ExtrasLength = 0;
	rs1->DataType     = 0;
	rs1->Status       = 0;
	rs1->BodyLength   = 0;
	rs1->Opaque       = 0;
	rs1->CAS          = 0;


	// Creating socket file descriptors
	if ( (sockfd_send = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("Send socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	if ( (sockfd_recv = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("Receive socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 

	buffer = malloc(MAXLINE);  

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	//servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT); 

	if (inet_pton(AF_INET, "128.197.176.148", &servaddr.sin_addr) <= 0) {
		printf("\nInvalid server address/ Address not supported \n");
		return -1;
	}	

	// Bind the socket with the server address 
	if ( bind(sockfd_recv, (const struct sockaddr *)&servaddr, 
				sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 


	uint8_t* buf_ptr;

	// Keep waiting for packets
	while(1){

		n = recvfrom(sockfd_recv, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buf_ptr = (uint8_t*) buffer;
		hdr = (MemCD_HDR_t*) buffer;

		if(hdr->Opcode == 0x00){ // Get request
			uint32_t key = ((MemCD_Get_Req_t *)buffer)->key;
			for(int i = 0; i < MAXPAYLOAD; i++){
				rg1->Data[i] = 0;
			}
			if(kvs.find(key) != kvs.end()){
				rg1->Status = 0x00;
				for (int i = 0; i < MAXPAYLOAD; i++){
					rg1->Data[i] = kvs[key][i];					                        
				}
			} else {
				rg1->Status = 0x01;
			}
			sendto(sockfd_send, rg1, sizeof(MemCD_GetResp_t), MSG_CONFIRM,
					(const struct sockaddr *) &cliaddr, sizeof(cliaddr)); 

		} else if(hdr->Opcode == 0x01){ // Set request received
			uint32_t key = ((MemCD_Set_Req_t *)buffer)->key;
			uint8_t *value = (uint8_t *)malloc(MAXPAYLOAD);
			for (int i = 0; i < MAXPAYLOAD; i++){	
				value[i] = ((MemCD_Set_Req_t *)buffer)->value[i];
			}
			kvs.insert(make_pair(key, value));
			sendto(sockfd_send, rs1, sizeof(MemCD_SetResp_t), MSG_CONFIRM,
					(const struct sockaddr *) &cliaddr, len);
		} else{
			printf("\nUnknown request received. Opcode = %x\n", hdr->Opcode);
		}
	}

	return 0;
}
