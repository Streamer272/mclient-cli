#include "term.h"

#include <unistd.h>
#include <termios.h>

struct termios term;

void term_init() {
    tcgetattr(STDIN_FILENO, &term);
}

void term_fuckup() {
    struct termios info;
    tcgetattr(0, &info);
    info.c_lflag &= ~ICANON;
    info.c_cc[VMIN] = 1;
    info.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &info);
}

void term_unfuck() {
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
