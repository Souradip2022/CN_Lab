#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(){
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

  binding = bind(sockfd, (struct sockaddr *) &sa, sizeof(sa));

  if (binding == -1) {
    printf("Binding failed\n");
  } else {
    printf("Bind successful\n");
  }

  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }
  int len = sizeof(sa);
  recvfrom(sockfd, buf, 100, 0, (struct sockaddr *) &sa, &len);

  for (int i = 0; i < 100; i++) {
    buf[i] = '\0';
  }
  strcpy(buf, "Message from server");
  sendto(sockfd, buf, 100, 0, (struct sockaddr *) &sa, sizeof(sa));

}