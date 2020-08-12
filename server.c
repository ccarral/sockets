/**
 * File              : server.c
 * Author            : Carlos Carral <carloscarral13@gmail.com>
 * Date              : 10/08/2020
 * Last Modified Date: 11/08/2020
 *
 * Simple socket server file
 *
 */

#include "error.h"
#include <asm-generic/socket.h>
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

  int socketfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];

  struct sockaddr_in serv_addr, cli_addr;

  int n;
  int opt = 1;

  if (argc < 2) {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  printf("Bienvenido\n");

  // Creating socket file descriptor
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  if (socketfd < 0)
    error("ERROR opening socket");

  CLEAR(serv_addr);

  portno = atoi(argv[1]);
  printf("Listening on port %d", portno);

  if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)))
    error("setsockopt");

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  if (listen(socketfd, 5) < 0)
    error("listen");

  clilen = sizeof(cli_addr);

  newsockfd =
          accept(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  if (newsockfd < 0)
    error("ERROR on accept");

  CLEAR(buffer);

  n = read(newsockfd, buffer, 256);

  if (n < -1)
    error("ERROR Reading from socket");

  printf("Message: %s\n", buffer);

  char *return_msg = "Message received";

  n = send(newsockfd, return_msg, strlen(return_msg), 0);

  if (n < 0)
    error("ERROR writing to socket");

  printf("Response sent");

  return 0;
}
