#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include "term.h"
#include "alloc.h"
#include "sound.h"
#include "socket.h"

pthread_t thread_id;
bool term_initialized = false;
bool sound_initialized = false;
bool socket_initialized = false;

void recv_loop(void *data);
void cleanup();

int main() {
    int ret = atexit(cleanup);
    if (ret != 0) {
        perror("atexit() failed");
        return EXIT_FAILURE;
    }

    term_init();
    term_initialized = true;
    sound_init();
    sound_initialized = true;

    printf("Enter server address: ");
    char *server_address = alloc(sizeof(char) * 16);
    fgets(server_address, 16, stdin);
    if (strcmp(server_address, "localhost\n") == 0) {
        strcpy(server_address, "127.0.0.1");
    }
    else {
        for (int i = 0; i < 16; i++) {
            char ch = server_address[i];
            if (!isdigit(ch) && ch != '.') server_address[i] = '\0';
        }
    }

    sock_init(server_address);
    socket_initialized = true;

    printf("Connected to %s\n", server_address);
    free(server_address);

    pthread_create(&thread_id, NULL, (void *(*)(void*)) &recv_loop, NULL);

    term_fuckup();
    while (true) {
        char ch = (char) getchar();
        if (ch == 'q')
            break;
        else if (ch != '.' && ch != '-')
            continue;

        char *message = alloc(2);
        message[0] = ch;
        message[1] = '\0';
        sock_send(message);
        free(message);
    }

    return EXIT_SUCCESS;
}

void recv_loop(void *data) {
    while (true) {
        char *message = sock_recv();
        if (strcmp(message, ".") == 0)
            sound_play(0.3f);
        else if (strcmp(message, "-") == 0)
            sound_play(0.6f);
        free(message);
    }
}

void cleanup() {
    pthread_cancel(thread_id);
    if (term_initialized) term_unfuck();
    if (sound_initialized) sound_exit();
    if (socket_initialized) sock_close();
}
