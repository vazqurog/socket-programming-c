#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/in.h>

int main() {

    /*
     === Client side work flow ===
    socket() -> connect() -> receive() -> close()
    */

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
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // Connect to port 
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("Error: Failed making a coneection to remote socket\n");
    } else {
        printf("Successfull Connection: port - %i\n", port);
    }

    // Receive data from the server
    char server_response[256];
    int recv_status = recv(network_socket, &server_response, sizeof(server_response) - 1, 0);
    if (recv_status == -1) {
        printf("Error: Packets not received\n");
    } else {
        printf("Packets Received\n");
    }

    // print server data
    printf("Packet data: %s\n", server_response);

    int close_status = close(network_socket);
    if (close_status == -1) {
        printf("Failed close connection: port - %i\n", port);
    } else {
        printf("Closed connectoion: port - %i\n", port);
    }
    return 0;
}
