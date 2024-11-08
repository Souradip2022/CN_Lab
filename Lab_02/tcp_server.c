#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main() {
  int sockfd, fd1, length, i;
  char buf[100]; /* We will use this buffer for communication */
  struct sockaddr_in sa, ta1;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = htons(60018);  // Use htons to convert to network byte order

  i = bind(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  if (i == -1) {
    perror("Bind failed");
    return 1;
  }
  printf("Bind successful. Server is listening on port 60018.\n");

  listen(sockfd, 5);

  while (1) {  // Loop to continuously accept connections
    length = sizeof(ta1);
    fd1 = accept(sockfd, (struct sockaddr *) &ta1, &length);
    if (fd1 == -1) {
      perror("Accept failed");
      continue; // Skip to the next iteration to accept another connection
    }

    printf("Client connected.\n");

    while (1) {  // Loop to continuously receive messages from the client
      memset(buf, '\0', sizeof(buf));  // Initialize buffer to 0 (using memset)

      int bytes_received = recv(fd1, buf, 100, 0);

      if (bytes_received <= 0) {  // Client disconnected or error
        printf("Client disconnected.\n");
        break;
      }

      printf("Received from client: %s\n", buf);

      // Respond to the client
      memset(buf, '\0', sizeof(buf));  // Initialize buffer to 0 (using memset)
      strcpy(buf, "Message from server");
      send(fd1, buf, 100, 0);
    }

    close(fd1);  // Close the connection with the current client
  }

  close(sockfd);  // Close the server socket (although this line won't be reached in the current loop)
  return 0;
}
