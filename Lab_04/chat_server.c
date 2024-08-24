#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
  int server_socket, client_socket, max_sd, sd, activity, valread;
  int client_sockets[MAX_CLIENTS] = {0};
  struct sockaddr_in server_addr, client_addr;
  socklen_t addrlen = sizeof(client_addr);
  char buffer[BUFFER_SIZE];
  fd_set readfds;

  // Create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Bind
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(8080);

  if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Listen
  if (listen(server_socket, MAX_CLIENTS) < 0) {
    perror("Listen failed");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port 8080\n");

  while (1) {
    // Clear the socket set
    FD_ZERO(&readfds);

    // Add server socket to set
    FD_SET(server_socket, &readfds);
    max_sd = server_socket;

    // Add client sockets to set
    for (int i = 0; i < MAX_CLIENTS; i++) {
      sd = client_sockets[i];

      // If valid socket descriptor then add to read list
      if (sd > 0)
        FD_SET(sd, &readfds);

      // Highest file descriptor number for select()
      if (sd > max_sd)
        max_sd = sd;
    }

    // Wait for activity on one of the sockets
    activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

    if ((activity < 0) && (errno != EINTR)) {
      printf("select error");
    }

    // If something happened on the server socket, it's an incoming connection
    if (FD_ISSET(server_socket, &readfds)) {
      if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
      }

      printf("New connection accepted\n");

      // Add new socket to array of sockets
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == 0) {
          client_sockets[i] = client_socket;
          printf("Adding to list of sockets as %d\n", i);
          break;
        }
      }
    }

    // Check each client socket
    for (int i = 0; i < MAX_CLIENTS; i++) {
      sd = client_sockets[i];

      if (FD_ISSET(sd, &readfds)) {
        // Check if it was for closing, and also read the incoming message
        if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
          // Someone disconnected, get details and close the socket
          getpeername(sd, (struct sockaddr *) &client_addr, &addrlen);
          printf("Host disconnected, ip %s, port %d\n",
                 inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

          // Close the socket and mark as 0 in list for reuse
          close(sd);
          client_sockets[i] = 0;
        } else {
          // Broadcast the message to all other clients
          buffer[valread] = '\0';
          for (int j = 0; j < MAX_CLIENTS; j++) {
            if (client_sockets[j] != 0 && client_sockets[j] != sd) {
              send(client_sockets[j], buffer, strlen(buffer), 0);
            }
          }
        }
      }
    }
  }

  return 0;
}
