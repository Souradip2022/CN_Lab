#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void bubbleSort(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

int main() {
  int server_fd, client_fd, valread;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int buffer[1024] = {0};

  // Create socket file descriptor
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Bind to the port 8080
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Start listening
  if (listen(server_fd, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  // Accept a client connection
  client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
  if (client_fd < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  // Read the array from the client
  valread = read(client_fd, buffer, sizeof(buffer));

  // The first element is the size of the array
  int n = buffer[0];

  // Sort the array
  bubbleSort(buffer + 1, n);

  // Send the sorted array back to the client
  send(client_fd, buffer, sizeof(buffer), 0);

  // Close the connection
  close(client_fd);
  close(server_fd);

  return 0;
}
