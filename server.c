#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr)
{

  char* filename = "serverFTPIYLI.txt";
  int i;
  char buffer[SIZE];
  socklen_t addr_size;

  // TO CREATE A FILE.
  FILE* fp = fp = fopen(filename, "w");

  // RECEIVE THE DATA AND ALSO WRITE THE DATA INTO THE FILE
  while (1)
  {
    addr_size = sizeof(addr);
    i = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_s>

    if (strcmp(buffer, "END") == 0)
    {
      break;
    }

    printf("[RECEVING] The Data Received From Client: %s", buffer);
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }

  fclose(fp);
}

int main()
{

  // TO DEFINE THE IP AND THE PORT
  char* ip = "192.168.56.103";
  const int port = 20;

  // DEFINE THE VARIABLES
  int server_sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[SIZE];
  int e;

  // UDP SOCKET CREATED
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0)
  {
    perror("[ERROR!] socket has error");
    exit(1);

  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_ad>
  if (e < 0)
  {
    perror("[ERROR!] bind error");
    exit(1);
  }

  printf("[STARTING] The UDP File Server has started. \n");
  write_file(server_sockfd, client_addr);

  printf("[SUCCESS] Data transfer has been completed.\n");
  printf("[CLOSING] Closing by shutting down the server.\n");
  close(server_sockfd);

  return 0;
}
