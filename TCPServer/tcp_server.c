#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // used on unix based
#include <netinet/in.h>

int main() {
    /*
    Server socket workflow 

    socket() -> bind() -> listen() -> accept()

    */

    char server_message[256] = "You have entered... the server\n";
    int port = 9002;
    
    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM,0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // bind the socket to out specified port
    int bind_status = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (bind_status == -1) {
        printf("Error: socket bind failed\n");
    } else {
        printf("Socket binded\n");
    }

    // listen to any packets coming to that port
    int listen_status = listen(server_socket, 5);

    if (listen_status == -1) {
        printf("Error: listening stopped\n");
    } else {
        printf("Listening for packets...\n");
    }    

    // accept connection
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1){
        printf("Denied: Client Connection\n");
    } else {
        printf("Accepted: Client Connection\n");
    }

    // send message
    int send_status = send(client_socket, server_message, sizeof(server_message), 0);

    if (send_status == -1) {
        printf("Failed to send packets to client\n");
    } else {
        printf("Packet sent\n");
    }

    // close socket
    int close_status = close(server_socket);

    if (close_status == -1) {
        printf("Failed to close connection to port %i\n", port);
    } else {
        printf("Closed connectoion to port %i\n", port);
    }

    return 0;
}