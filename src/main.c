#include <stdio.h>
#include "sound.h"
#include <unistd.h>

int main() {
    init_al();
    play(0.6f);
    sleep(1);
    play(0.3f);
    exit_al();
    printf("Hello, World!\n");
    return 0;
}
