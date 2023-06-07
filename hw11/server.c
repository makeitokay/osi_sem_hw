#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/random.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);

    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    client_address_length = sizeof(client_address);

    int client1 = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
    int client2 = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);

    char buffer[1024];

    while (1) {
        int received = recv(client1, buffer, sizeof(buffer), 0);
        printf("Received bytes: %d\n", received);
        if (received < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        buffer[received] = '\0';
        send(client2, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "The End\n") == 0) {
            break;
        }
    }

    close(client1);
    close(client2);
    close(server_socket);

    return 0;
}