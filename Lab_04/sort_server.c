#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void bubbleSort(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
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
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  // Bind to port 8080
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  // Start listening
  if (listen(server_fd, 3) < 0) {
    perror("Listen failed");
    exit(EXIT_FAILURE);
  }
  printf("Server listening on port 8080...\n");

  // Accept a client connection
  printf("Waiting for a client to connect...\n");
  if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
    perror("Accept failed");
    exit(EXIT_FAILURE);
  }
  printf("Client connected.\n");

  // Read the array from the client
  printf("Receiving array from the client...\n");

  valread = recv(client_fd, buffer, sizeof(buffer), 0);
  if (valread < 0) {
    perror("Recv failed");
    exit(EXIT_FAILURE);
  }

  printf("Array received from the client.\n");

  // The first element is the size of the array
  int n = buffer[0];
  printf("Number of elements to sort: %d\n", n);
  printf("Array before sorting: ");
  for (int i = 1; i <= n; i++) {
    printf("%d ", buffer[i]);
  }
  printf("\n");

  // Sort the array
  bubbleSort(buffer + 1, n);
  printf("Array sorted.\n");

  // Send the sorted array back to the client
  printf("Sending sorted array back to the client...\n");
  send(client_fd, buffer, sizeof(buffer), 0);
  printf("Sorted array sent to the client.\n");

  // Close the connection
  printf("Closing connection.\n");
  close(client_fd);
  close(server_fd);

  return 0;
}
