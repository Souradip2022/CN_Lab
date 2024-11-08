#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main() {
  int sockfd;
  char buf[100];
  struct sockaddr_in sa;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  sa.sin_port = htons(60018);

  if (connect(sockfd, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
    perror("Connection failed");
    return 1;
  }

  printf("Connected to the server.\n");

  memset(buf, 0, sizeof(buf));
  printf("Enter base salary: ");
  fgets(buf, sizeof(buf), stdin);

  buf[strcspn(buf, "\n")] = 0;
  send(sockfd, buf, strlen(buf), 0);

  memset(buf, 0, sizeof(buf));
  recv(sockfd, buf, sizeof(buf), 0);
  printf("Received gross salary from server: %s\n", buf);

  close(sockfd);
  printf("Disconnected from the server.\n");

  return 0;
}