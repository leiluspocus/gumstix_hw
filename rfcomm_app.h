/**
 *  Brief  : Including librairies used by both client and server apps
 *  Author : Laila Atrmouh
 */
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include "bluetooth.h"
#include "rfcomm.h"

void error(char msg[]) {
	perror(msg);
	exit(EXIT_FAILURE);
}
