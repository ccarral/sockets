/**
 * File              : error.c
 * Author            : Carlos Carral <carloscarral13@gmail.com>
 * Date              : 10.08.2020
 * Last Modified Date: 10.08.2020
 */

#include <stdio.h>
#include <stdlib.h>

void error(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}
