#include <stdio.h>
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

void recv_loop(void *data);
void cleanup();

int main() {
    sound_init();
    term_init();
    sock_init();

    int ret = atexit(cleanup);
    if (ret != 0) {
        perror("atexit() failed");
        return EXIT_FAILURE;
    }

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
    term_unfuck();
    sound_exit();
    sock_close();
}
