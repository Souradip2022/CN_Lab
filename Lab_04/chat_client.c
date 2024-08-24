#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

void *receive_messages(void *socket_desc) {
  int sock = *(int *)socket_desc;
  char buffer[BUFFER_SIZE];
  int valread;

  while ((valread = read(sock, buffer, sizeof(buffer))) > 0) {
    buffer[valread] = '\0';
    printf("Server: %s\n", buffer);
  }

  return NULL;
}

int main() {
  int sock;
  struct sockaddr_in server_addr;
  char message[BUFFER_SIZE];
  pthread_t recv_thread;

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Connect to server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

  printf("Connected to server\n");

  // Start the thread to receive messages
  if (pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock) < 0) {
    perror("Could not create thread");
    close(sock);
    exit(EXIT_FAILURE);
  }

  // Send messages
  while (1) {
    fgets(message, BUFFER_SIZE, stdin);
    if (send(sock, message, strlen(message), 0) < 0) {
      perror("Send failed");
      break;
    }
  }

  close(sock);
  return 0;
}
