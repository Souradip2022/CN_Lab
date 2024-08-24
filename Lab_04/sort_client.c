#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  int array[1024] = {5, 3, 2, 4, 1};  // Example array
  int n = 5;  // Number of elements in the array

  int buffer[1024] = {0};
  buffer[0] = n;
  memcpy(buffer + 1, array, n * sizeof(int));

  // Create socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  // Connect to the server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  // Send the array to the server
  send(sock, buffer, sizeof(buffer), 0);

  // Read the sorted array from the server
  valread = read(sock, buffer, sizeof(buffer));

  // Print the sorted array
  printf("Sorted array: ");
  for (int i = 1; i <= buffer[0]; i++) {
    printf("%d ", buffer[i]);
  }
  printf("\n");

  // Close the socket
  close(sock);

  return 0;
}
