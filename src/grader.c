#include <stdint.h>
#include <stdlib.h>

#include "structs/course.h"
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

    struct course *course_test = course_alloc("CS", 2505, "Introduction to Computer Organization", 3);
    course_regrade(course_test, GRADE_A);

    char *output = course_alloc_details(course_test);

    int *fail;
    if (print(output, fail) == FAIL) {
        exit(2);
    }

    course_free(course_test);
    free(output);
}

