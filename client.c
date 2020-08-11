/**
 * File              : client.c
 * Author            : Carlos Carral <carloscarral13@gmail.com>
 * Date              : 10.08.2020
 * Last Modified Date: 10.08.2020
 *
 * Simple socket client file
 *
 */

#include "error.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

int main(int argc, char **argv)
{
  int socketfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];

  if (argc < 3) {
    fprintf(stderr, "usage: %s hostname port", argv[0]);
    exit(EXIT_FAILURE);
  }

  portno = atoi(argv[2]);
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if (socketfd < 0)
    error("ERROR opening socket\n");

  server = gethostbyname(argv[1]);

  if (server == NULL) {
    fprintf(stderr, "ERROR: No such host");
    exit(EXIT_FAILURE);
  }

  CLEAR(serv_addr);

  serv_addr.sin_family = AF_INET;

  bcopy((char *)&server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);

  serv_addr.sin_port = htons(portno);

  if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  printf("Please enter the message: ");
  CLEAR(buffer);
  fgets(buffer, 255, stdin);

  n = write(socketfd, buffer, strlen(buffer));

  if (n < 0)
    error("ERROR Writing to socket");

  CLEAR(buffer);

  n = read(socketfd, buffer, 255);

  if (n < 0)
    error("ERROR Reading from socket");

  printf("%s\n", buffer);
  return 0;
}
