/**
 * Brief : Client Side Application
 * Author: Laila Atrmouh
 **/

#include "rfcomm_app.h"

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int socketfd, status;
    if ( argc == 1 ) {
    	error("Address of server missing: ./rfcomm_client <Address server>");
    }
    char dest[18] = argv[1];

    // allocate a socket
    socketfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	if ( socketfd < 0 ) {
		error("Error while creating socket - Client");	
	}
	
    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    status = connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    
    // Sending a message
    if( status == 0 ) {
    	char msg[100] = "I'm Laila and my project is a revolutionnary file transfer application for gumstix boards !";
    	printf("I'm the client and I will send a message: %s", msg);
        status = write(sockefd, msg, strlen(msg));
        if ( status < 0 ) { 
        	error("Error while sending message to server - Client") ; 
        }
    }

    if( status < 0 ) {
    	error("Error while connecting to Server");
    }
	// Closing socket
    close(socketfd);
    return 0;
}