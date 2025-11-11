#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // used to close socket on unix based

#include <netinet/in.h>

int main() {
    /*
    Server socket workflow 

    socket() -> bind() -> listen() -> accept()

    */

    char server_message[256] = "You have reached the server!\n";
    int port = 9002;
    
    // create sercer socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM,0);

    //define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    // bind the socket to out specified port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen to any packets coming to that port
    listen(server_socket, 5);

    // accept connection
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // send message
    send(client_socket, server_message, sizeof(server_message), 0);

    // close socket
    close(server_socket);

    return 0;
}