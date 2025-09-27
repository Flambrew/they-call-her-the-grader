#include <stdint.h>
#include <stdlib.h>

#include "utils/printer.h"

struct transcript {
    struct course *list;
};

int transcript_add() {

}

enum command_state {
    STARTUP
};

int command_parse(const int argc, char **argv, enum command_state state) {
    char *command = argv[1];
    switch (state) {
        case STARTUP:

        break;
    }

    return 0;
}





const char *TXT_ENTRY = "f>+-\n" \
        "x>|$WELCOME TO THE GRADER$|\n" \
        "f>| \n" \
        "x>|$(use help for command summary)$|\n" \
        "f>+-";

int main(const int argc, const char** argv) {
    int *fail;
    if (print(TXT_ENTRY, fail) == FAIL) {
        exit(2);
    }

    // enum command_state state = STARTUP;
    // while (command_parse(argc, argv, state));
    // return 0;
}

