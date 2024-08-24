#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int client_socket, char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    perror("File not found");
    return;
  }

  char buffer[BUFFER_SIZE];
  bzero(buffer, BUFFER_SIZE);
  int bytes_read;
  while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
    write(client_socket, buffer, bytes_read);
    bzero(buffer, BUFFER_SIZE);
  }
  fclose(file);
}

int main(int argc, char *argv[]) {
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_size;
  char buffer[BUFFER_SIZE];

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Binding failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  if (listen(server_socket, 5) < 0) {
    perror("Listening failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on port %d...\n", PORT);

  while (1) {
    client_addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_socket < 0) {
      perror("Connection acceptance failed");
      continue;
    }

    printf("Client connected!\n");

    // Send the list of files in the server directory
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
      bzero(buffer, BUFFER_SIZE);
      while ((dir = readdir(d)) != NULL) {
        if (dir->d_type == DT_REG) {
          strcat(buffer, dir->d_name);
          strcat(buffer, "\n");
        }
      }
      closedir(d);
    }
    write(client_socket, buffer, strlen(buffer));

    // Receive the filename the client wants to download
    bzero(buffer, BUFFER_SIZE);
    read(client_socket, buffer, BUFFER_SIZE);
    printf("Client requested file: %s\n", buffer);

    // Send the requested file to the client
    send_file(client_socket, buffer);

    // Close the connection after file transfer
    close(client_socket);
    printf("Client disconnected!\n");
  }

  close(server_socket);
  return 0;
}