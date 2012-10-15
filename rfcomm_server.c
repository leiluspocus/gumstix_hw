/**
 * Brief :Server side Application
 * Author: Laila Atrmouh
 */
#include "rfcomm_app.h"

int main() {
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int socketfd, client, length_bytes_read, testCall;
    socklen_t opt = sizeof(rem_addr);

    // Creation of the socket
    socketfd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	if ( socketfd < 0 ) { 
		error("Failure creating socket - Server"); 
	}
	
    // Binding socket 
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    
    testCall = bind(socketfd, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

	if ( testCall < 0 ) { error("Failure Bind - Server"); }
	
    // Putting socket in the listening mode
    testCall = listen(socketfd, 1);
	if ( testCall < 0 ) { error("Failure Listen - Server"); }
	
    // Accept one connection
    client = accept(socketfd, (struct sockaddr *)&rem_addr, &opt);
	if ( client < 0 ) { error("Failure Accept - Server"); }
	
    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    length_bytes_read = read(client, buf, sizeof(buf));
    if( length_bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }
    else {
    	error("Reading data from client - Server");
    }

    // close connection
    close(client);
    
    // close socket
    close(socketfd);
    
    return 0;
}
