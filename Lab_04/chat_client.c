#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
  int sockfd;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server_addr;
  socklen_t addr_len = sizeof(server_addr);

  // Create UDP socket
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  while (1) {
    // Get message from client user
    printf("Client: ");
//    fgets(buffer, BUFFER_SIZE, stdin);
    scanf("%s", buffer);
    // Send message to server
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &server_addr, addr_len) < 0) {
      perror("Send failed");
      continue;
    }

    // Receive reply from server
    memset(buffer, 0, BUFFER_SIZE);
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &server_addr, &addr_len);
    if (n < 0) {
      perror("Receive failed");
      continue;
    }
    buffer[n] = '\0';
    printf("Server: %s\n", buffer);
  }

  close(sockfd);
  return 0;
}
