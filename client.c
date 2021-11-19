#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 1024

void send_file_data(FILE* fp, int sockfd, struct sockaddr_in addr)
{
  int n;
  char buffer[SIZE];

  // SENDING THE DATA
  while (fgets(buffer, SIZE, fp) != NULL)
  {
    printf("[SENDING] Data will be sent: %s", buffer);

    n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
    if (n == -1)
    {
    {
      perror("[ERROR!] Failed on sending the data to the server.");
      exit(1);
    }
    bzero(buffer, SIZE);
  }

  // TERMINATE THE SESSION
  strcpy(buffer, "END");
  sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));

  fclose(fp);
}

int main(void)
{
  // TO DEFINE THE IP AND THE PORT
  char *ip = "192.168.56.103";
  const int port = 20;

  // DEFINE THE VARIABLES
  int server_sockfd;
  struct sockaddr_in server_addr;
  char *filename = "clientFTP.txt";
  FILE *fp = fopen(filename, "r");

  // THE UDP SOCKET WILL BE CREATED
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0)
  {
    perror("[ERROR!] Error on finding the socket");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);


  // READING THE FILE
  if (fp == NULL)
  {
    perror("[ERROR!] Failed on reading the file ");
    exit(1);
  }

  // THE DATA WILL BE SENT TO THE SERVER
  send_file_data(fp, server_sockfd, server_addr);

  printf("[SUCCESS] Completed the data transfer.\n");
  printf("[CLOSING] The data from the server will be disconnected.\n");

  close(server_sockfd);

  return 0;
}

