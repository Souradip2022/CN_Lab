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
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_len = sizeof(client_addr);

  // Create UDP socket
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Bind the socket to the port
  if (bind(sockfd, (const struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  printf("Server is running on port %d\n", PORT);

  while (1) {
    memset(buffer, 0, BUFFER_SIZE);

    // Receive message from client
    int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &addr_len);
    if (n < 0) {
      perror("Receive failed");
      continue;
    }
    buffer[n] = '\0';
    printf("Client: %s\n", buffer);

    // Get reply message from server user
    printf("Server: ");
//    fgets(buffer, BUFFER_SIZE, stdin);
    scanf("%s", buffer);
    // Send reply to client
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client_addr, addr_len);
  }

  close(sockfd);
  return 0;
}
