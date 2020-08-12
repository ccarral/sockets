/**
 * File              : client.c
 * Author            : Carlos Carral <carloscarral13@gmail.com>
 * Date              : 10/08/2020
 * Last Modified Date: 11/08/2020
 *
 * Simple socket client file
 *
 */

#include "error.h"
#include <arpa/inet.h>
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

  if (argc < 2) {
    fprintf(stderr, "usage: %s hostname port", argv[0]);
    exit(EXIT_FAILURE);
  }

  printf("Bienvenido\n");

  portno = atoi(argv[1]);
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Requested socket\n");

  if (socketfd < 0)
    error("ERROR opening socket\n");

  /* server = gethostbyname(argv[1]); */
  /* printf("Got a server with name: %s", server->h_name); */

  /* if (server == NULL) { */
  /* fprintf(stderr, "ERROR: No such host"); */
  /* exit(EXIT_FAILURE); */
  /* } */

  CLEAR(serv_addr);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);

  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0) {
    error("Invalid address\n");
  }

  /* bcopy((char *)&server->h_addr, (char *)&serv_addr.sin_addr.s_addr, */
  /* server->h_length); */

  if (connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  printf("Please enter the message: ");
  CLEAR(buffer);
  fgets(buffer, 255, stdin);

  n = send(socketfd, buffer, strlen(buffer), 0);

  if (n < 0)
    error("ERROR Writing to socket");

  CLEAR(buffer);

  n = read(socketfd, buffer, 256);

  if (n < 0)
    error("ERROR Reading from socket");

  printf("%s\n", buffer);
  return 0;
}
