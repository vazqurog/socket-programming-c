#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {

    // Create a socket
    int network_socket;
    
    // - ADF_INET specifies IPv4 for comms 
    // - SOCK_STREAM: socket type - bidirectional, sequenced data
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;

    // Specify connection port: 9002
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY();

    return 0;
}