#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "term.h"
#include "sound.h"
#include "socket.h"

int main() {
    sound_init();
    term_init();
    sock_init();
    /*term_fuckup();

    printf("Start typing: ");
    char ch = (char) getchar();
    printf("You entered '%d'\n", ch);*/
    sock_send("hey there little fella");

    char *message = sock_recv();
    printf("got '%s'\n", message);

    sound_exit();
    sock_close();
    return EXIT_SUCCESS;
}
