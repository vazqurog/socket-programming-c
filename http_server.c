#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

int main() {
    // create file object, open in read
    FILE *html_data;
    html_data = fopen("index.html", "r");

    // read file data into response
    char response_data[1024];
    fgets(response_data, 1024, html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n"
    strcat(http_header, response_data);

    // create socket
    int server_socket;
    int port;
    server_socket = socker(AF_INET, SOCK_STREAM, 0);
    port = 8001;

    struct sockaddr_in ser
    server_address.sin_family = AF_INET;

    // specify port
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

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

    int client_socket;
    
    while(1) {
        // acccept connection
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);

    }
    return 0;
}