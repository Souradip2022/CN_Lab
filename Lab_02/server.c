#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

int main() {
  int sockfd, fd1, length, i, sum;
  char buf[100], p[3]; /* We will use this buffer for communication */
  struct sockaddr_in sa, ta1;

/* The following system call opens a socket. The first parameter
indicates the family of the protocol to be followed. For internet
protocols we use AF_INET. For TCP sockets the second parameter
is SOCK_STREAM. The third parameter is set to 0 for user
applications.*/
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

/* The structure "sockaddr_in" is defined in <netinet/in.h> for the
internet family of protocols. This has three main fields. The
field "sin_family" specifies the family and is therefore AF_INET
for the internet family. The field "sin_addr" specifies the
internet address of the server. This field is set to INADDR_ANY
for machines having a single IP address. The field "sin_port"
specifies the port number of the server.*/
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = 60018;

/* With the information provided in serv_addr, we associate the server
with its port using the bind() system call. */
  i = bind(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  printf("test %d %d\n", sockfd, i);

/* This specifies that up to 5 concurrent client
requests will be queued up while the system is
executing the "accept" system call below.*/
  listen(sockfd, 5);

/* The accept() system call accepts a client connection.
It blocks the server until a client request comes.

The accept() system call fills up the client's details
in a struct sockaddr which is passed as a parameter.
The length of the structure is noted in clilen. Note
that the new socket descriptor returned by the accept()
system call is stored in "fd1".*/

  length = sizeof(sa);
  fd1 = accept(sockfd, (struct sockaddr *) &ta1, &length);
/* We initialize the buffer, copy the message to it,
and send the message to the client. */
  for (i = 0; i < 100; i++) buf[i] = '\0';
  strcpy(buf, "Message from server");
  send(fd1, buf, 100, 0);

/* We again initialize the buffer, and receive a
message from the client. */
  for (i = 0; i < 100; i++) buf[i] = '\0';
  recv(fd1, buf, 100, 0);
  printf("%s\n", buf);

}
