//
// Created by makeitokay on 04.06.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char* server_ip = argv[1];
    int port = atoi(argv[2]);

    int client_socket;
    struct sockaddr_in server_address;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server: %s:%d\n", server_ip, port);

    char* buffer = malloc(1024 * sizeof(char));
    while (1) {
        printf("Message: ");
        fgets(buffer, sizeof(buffer), stdin);
        printf("Sending %ld bytes\n", strlen(buffer));
        send(client_socket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "The End\n") == 0) {
            break;
        }
    }

    close(client_socket);
    return 0;
}