#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {

    // Create a socket
    int network_socket;
    int port = 9002;
    
    // - ADF_INET specifies IPv4 for comms 
    // - SOCK_STREAM: socket type - bidirectional, sequenced data
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;

    // Specify port: 9002
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY();
    
    // Connect to port
    int conection_status = connect(network_socket, (struct sockaddr * ) &server_address, sizeof(server_address));

    if (connection_status == -1) {
        printf("Error:Failed making a coneection to remote socket\n");
    } else {
        prtinf("Successfully connected to remote socket\n");
    }

    // Receive data from the server
    char server_response[256];
    receive(network_socket, &server_response, sizeof(server_response), 0);

    // print server data
    printf("Server response: %s\n", server_response);

    close(sock);
    return 0;
}