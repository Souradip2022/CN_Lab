#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <stdlib.h>

int main() {
  int sockfd, fd1, length, i;
  char buf[100];
  struct sockaddr_in sa, ta1;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_port = htons(60018);

  i = bind(sockfd, (struct sockaddr *) &sa, sizeof(sa));
  if (i == -1) {
    perror("Bind failed");
    return 1;
  }
  printf("Bind successful. Server is listening on port 60018.\n");

  listen(sockfd, 5);

  while (1) {
    length = sizeof(ta1);
    fd1 = accept(sockfd, (struct sockaddr *) &ta1, &length);
    if (fd1 == -1) {
      perror("Accept failed");
      continue;
    }

    printf("Client connected.\n");

    while (1) {
      memset(buf, 0, sizeof(buf));
      int bytes_received = recv(fd1, buf, sizeof(buf), 0);

      if (bytes_received <= 0) {
        printf("Client disconnected.\n");
        break;
      }

      printf("Received from client: %s\n", buf);

      double base_salary = atof(buf);
      double gross_salary = base_salary + 0.5 * base_salary + 0.15 * base_salary;

      memset(buf, 0, sizeof(buf));
      snprintf(buf, sizeof(buf), "%.2f", gross_salary);
      send(fd1, buf, sizeof(buf), 0);

      printf("Sent to client: Gross Salary = %.2f\n", gross_salary);
    }

    close(fd1);
  }

  close(sockfd);
  return 0;
}
