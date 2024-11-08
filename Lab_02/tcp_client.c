#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main() {
  int i, sockfd;
  char buf[100];
  struct sockaddr_in sa;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback IP address
  sa.sin_port = htons(60018);  // Use htons to convert to network byte order

  i = connect(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  if (i == -1) {
    perror("Connection failed");
    return 1;
  }

  printf("Connected to the server.\n");

  while (1) {  // Loop to continuously send and receive messages
    // Clear the buffer and get input from the user
    for (i = 0; i < 100; i++) buf[i] = '\0';
    printf("Enter a message to send to the server (or type 'exit' to quit): ");
    fgets(buf, 100, stdin);

    // Remove newline character from the input
    buf[strcspn(buf, "\n")] = 0;

    // Check if the user wants to exit
    if (strcmp(buf, "exit") == 0) {
      break;
    }

    // Send the message to the server
    send(sockfd, buf, strlen(buf), 0);

    // Clear the buffer and receive the response from the server
    for (i = 0; i < 100; i++) buf[i] = '\0';
    recv(sockfd, buf, 100, 0);
    printf("Received from server: %s\n", buf);
  }

  close(sockfd);  // Close the socket when done
  printf("Disconnected from the server.\n");
  return 0;
}
