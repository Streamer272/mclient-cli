#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "alloc.h"

#define BUFFER_SIZE 1024

int sock;
int client_fd;

void sock_init() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() faile");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(4096);

    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        perror("inet_pton() failed");
        exit(EXIT_FAILURE);
    }

    if ((client_fd = connect(sock, (struct sockaddr*) &address, sizeof(address))) < 0) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
}

void sock_send(char *message) {
    send(sock, message, strlen(message), 0);
}

char *sock_recv() {
    char *buffer = alloc(BUFFER_SIZE);
    read(sock, buffer, BUFFER_SIZE);
    return buffer;
}

void sock_close() {
    close(client_fd);
    sock = -1;
    client_fd = -1;
}
