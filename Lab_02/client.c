#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

int main() {
  int i, sockfd;
  char buf[100];
  struct sockaddr_in sa;

/* Opening a socket is exactly similar to the server process */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

/* Recall that we specified INADDR_ANY when we specified the server
address in the server. Since the client can run on a different
machine, we must specify the IP address of the server.

TO RUN THIS CLIENT, YOU MUST CHANGE THE IP ADDRESS SPECIFIED
BELOW TO THE IP ADDRESS OF THE MACHINE WHERE YOU ARE RUNNING
THE SERVER.*/
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr("127.0.0.1"); //Loop back IP address
  sa.sin_port = 60018;

/* With the information specified in serv_addr, the connect()
system call establishes a connection with the server process.*/
  i = connect(sockfd, (struct sockaddr *) &sa, sizeof(sa));

/* After connection, the client can send or receive messages.
However, please note that recv() will block when the
server is not sending and vice versa. Similarly send() will
block when the server is not receiving and vice versa. For
non-blocking modes, refer to the online man pages.*/
  for (i = 0; i < 100; i++) buf[i] = '\0';
  recv(sockfd, buf, 100, 0);
  printf("%s\n", buf);

  for (i = 0; i < 100; i++) buf[i] = '\0';
  strcpy(buf, "Message from client");
  send(sockfd, buf, 100, 0);

}
