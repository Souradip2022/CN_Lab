#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  int n;

  printf("Enter the number of elements: ");
  scanf("%d", &n);
  int array[n];
  printf("Enter the elements:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  int buffer[1024] = {0};
  buffer[0] = n;
  memcpy(buffer + 1, array, n * sizeof(int));

  // Create socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Socket creation error\n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(8080);


  // Connect to the server
  printf("Connecting to the server...\n");
  if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("Connection Failed\n");
    return -1;
  }
  printf("Connected to the server.\n");

  // Send the array to the server
  printf("Sending array to the server...\n");
  send(sock, buffer, sizeof(buffer), 0);
  printf("Array sent to the server.\n");

  // Read the sorted array from the server
  valread = recv(sock, buffer, sizeof(buffer), 0);
  if (valread <= 0) {
    perror("Unable to receive value form sorted array");
    exit(EXIT_FAILURE);
  }
  printf("Received sorted array from the server.\n");

  // Print the sorted array
  printf("Sorted array: ");
  for (int i = 1; i <= buffer[0]; i++) {
    printf("%d ", buffer[i]);
  }
  printf("\n");

  // Close the socket
  printf("Closing connection.\n");
  close(sock);

  return 0;
}
