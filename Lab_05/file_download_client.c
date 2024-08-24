
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  int client_socket;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE];

  if (argc != 2) {
    printf("Usage: %s <Server IP>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
    perror("Invalid address or address not supported");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  // Receive the list of files from the server
  bzero(buffer, BUFFER_SIZE);
  read(client_socket, buffer, BUFFER_SIZE);
  printf("Files available on the server:\n%s\n", buffer);

  // Get the filename from the user
  printf("Enter the name of the file you want to download: ");
  bzero(buffer, BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, stdin);
  buffer[strcspn(buffer, "\n")] = 0;  // Remove trailing newline character

  // Send the filename to the server
  write(client_socket, buffer, strlen(buffer));

  // Receive the file and save it
  FILE *file = fopen(buffer, "wb");
  if (file == NULL) {
    perror("File creation failed");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  bzero(buffer, BUFFER_SIZE);
  int bytes_read;
  while ((bytes_read = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
    fwrite(buffer, sizeof(char), bytes_read, file);
    bzero(buffer, BUFFER_SIZE);
  }

  fclose(file);
  printf("File downloaded successfully!\n");

  // Close the connection
  close(client_socket);
  return 0;
}