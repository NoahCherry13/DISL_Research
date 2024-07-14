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

#define PORT	 44000
#define MAXLINE 4096
#define MAXPAYLOAD 16 // Size of value in Bytes

#define GIG 1000000000
#define SIZES 1           // MAKE 7
#define ITERS 2

#define SEED 513

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
} MemCD_Resp_t;


int main(int argc, char *argv[])
{
  struct timespec diff(struct timespec start, struct timespec end);
  struct timespec time1, time2;
  int clock_gettime(clockid_t clk_id, struct timespec *tp);

  int GetReqs;
  int SetReqs;
  int GetFail;
  int GetSuccess;
  int SetFail;
  int SetSuccess;
  int SIZE;
  int iter;
  int NUM_ITER;
  uint64_t roundtrip_time;

	int sockfd_send, sockfd_recv; 
	void *buffer; 
	struct sockaddr_in servaddr, cliaddr; 
  MemCD_Set_Req_t *s1;
  MemCD_Get_Req_t *g1;
  MemCD_Resp_t    *r1;
	int n;
	socklen_t len; 

  if(argc < 2){
    printf("Value size defaulted to %d Bytes.\n", MAXPAYLOAD);
    SIZE = MAXPAYLOAD;
    printf("Number of iterations defaulted to 100.");
    NUM_ITER = 100;
  } else if(argc < 3){
    SIZE = atoi(argv[1]);
    printf("Number of iterations defaulted to 100.");
    NUM_ITER = 100;
  } else{
    SIZE = atoi(argv[1]);
    NUM_ITER = atoi(argv[2]);
  }

  struct timespec time_stamp[NUM_ITER];

  GetReqs = 0;
  SetReqs = 0;
  GetFail = 0;
  GetSuccess = 0;
  SetFail = 0;
  SetSuccess = 0;

  buffer = malloc(MAXLINE);  

  printf("Size of MemCD_HDR_t : %d\n", sizeof(MemCD_HDR_t));
  printf("Size of MemCD_Set_Req_t : %d\n", sizeof(MemCD_Set_Req_t));
  printf("Size of MemCD_Get_Req_t : %d\n", sizeof(MemCD_Get_Req_t));

  g1 = (MemCD_Get_Req_t*) malloc(sizeof(MemCD_Get_Req_t));
  s1 = (MemCD_Set_Req_t*) malloc(sizeof(MemCD_Set_Req_t));

  g1->header.Magic        = 0x80;
  g1->header.Opcode       = 0x00;
  g1->header.KeyLength    = 4;
  g1->header.ExtrasLength = 0;
  g1->header.DataType     = 0;
  g1->header.vbucketID    = 0;
  g1->header.BodyLength   = 4; // key
  g1->header.Opaque       = 0;
  g1->header.CAS          = 0;

  s1->header.Magic        = 0x80;
  s1->header.Opcode       = 0x01;
  s1->header.KeyLength    = 4;
  s1->header.ExtrasLength = 8;
  s1->header.DataType     = 0;
  s1->header.vbucketID    = 0;
  s1->header.BodyLength   = 28; // key + extra + value = 4+8+16
  s1->header.Opaque       = 0;
  s1->header.CAS          = 0;
  s1->extras_flags        = 0;
  s1->extras_expiration   = 0;


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
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
  if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0) {
      printf("\nInvalid server address/ Address not supported \n");
      return -1;
  }	

  // Filling client information
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, "127.0.0.1", &cliaddr.sin_addr) <= 0) {
      printf("\nInvalid client address/ Address not supported \n");
      return -1;
  }	

	// Bind the socket with the server address 
	if ( bind(sockfd_recv, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

  
  // Initialize rand()
  srand(SEED);

  // Running tests
  // Set requests 
  printf("\nSet requests...\n");
  while(SetSuccess < NUM_ITER){ // Go on until there are NUM_ITER entries in the KVS
    s1->key = rand();
    for(int i=0; i<SIZE; i++){
      s1->value[i] = rand();
    }

    SetReqs++;
    sendto(sockfd_send, s1, sizeof(MemCD_Set_Req_t), MSG_CONFIRM,
          (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
    n = recvfrom(sockfd_recv, buffer, MAXLINE, MSG_WAITALL, NULL, &len);
    r1 = (MemCD_Resp_t *) buffer;
    if(r1->Opcode == 0x01 && r1->Status == 0x00){ // Successful Set request
      SetSuccess++;
    } else{
      SetFail++;
    }
  }

  // Re-initialize the random number generator
  srand(SEED);
  printf("\n\nRunning get tests...\n");

  while(GetSuccess < NUM_ITER){ // Go on until we have read NUM_ITER entries successfully
    g1->key = rand();
    GetReqs++;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    sendto(sockfd_send, g1, sizeof(MemCD_Get_Req_t), MSG_CONFIRM,
          (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
    n = recvfrom(sockfd_recv, buffer, MAXLINE, MSG_WAITALL, NULL, &len);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

    r1 = (MemCD_Resp_t *) buffer;
    if(r1->Opcode == 0x00 && r1->Status == 0x00){ // Successful Get request
      time_stamp[GetSuccess] = diff(time1,time2);
      GetSuccess++;
    } else{
      GetFail++;
    }
  }

  // Print timing results
  printf("\nGet times..\n");
  for (int i = 0; i < NUM_ITER; i++) {
    roundtrip_time = (uint64_t) GIG*time_stamp[i].tv_sec + time_stamp[i].tv_nsec;
    printf("%8ld\n", roundtrip_time);
  }

  // Print stats
  printf("\n\n SetReqs = %d\n", SetReqs);
  printf("SetSuccess = %d\n", SetSuccess);
  printf("SetFail = %d\n", SetFail);
  printf("\n GetReqs = %d\n", GetReqs);
  printf("GetSuccess = %d\n", GetSuccess);
  printf("GetFail = %d\n", GetFail);

  return 0;
}



/*************************************************/
struct timespec diff(struct timespec start, struct timespec end)
{
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

double fRand(double fMin, double fMax)
{
    double f = (double)random() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}



/****************************************************/
