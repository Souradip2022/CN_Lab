#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main() {

  int sockfd, binding;
  char buf[100];
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    printf("Socket failed\n");
  } else {
    printf("Socket creation successful\n");
  }

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(3000);
  sa.sin_addr.s_addr = inet_addr("127.0.0.1");

  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }
  strcpy(buf, "Message from client");
  sendto(sockfd, buf, 100, 0, (struct sockaddr *) &sa, sizeof(sa));

  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }

  int len = sizeof(sa);
  recvfrom(sockfd, buf, 100, 0, (struct sockaddr *) &sa, &len);

  printf("Message receive from server from IP: %s and port: %i\n",
         inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
  printf("Message from server: %s\n", buf);
}