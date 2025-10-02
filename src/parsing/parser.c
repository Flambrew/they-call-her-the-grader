#include <stdbool.h>
#include <stdint.h>

#include "../structs/transcript.h"

/**
 * Equality test for strings. 
 * Return true if equal and null terminated, false otherwise.
 */
static bool string_equals(const char *a, const char *b) {
    uint32_t i;
    for (i = 0; i < MAX_CHARS_PER_LINE; ++i) {
        if (a[i] != b[i]) {
            return false;
        } else if (a[i] == '\0') {
            return true;
        }
    }

    return false;
}

/**
 * Unsigned integer parse for strings.
 * Return 2^32-1 on invalid string.
 */
static uint32_t string_readint(const char *str) {
    uint8_t i;
    uint32_t out = 0;
    for (i = 0; i < 10; ++i) {
        if (str[i] == '\0') break;
        if (str[i] >= '0' && str[i] <= '9') {
            out = out * 10 + str[i] - '0';
        }
    }

    if (i == 0) 
        return -1;
    return out;
}

enum state_type {
    ENTRY,
    TRANSCRIPT
};

static enum result entry_list(struct transcript *transcript) { return FAIL; }
static enum result entry_open(struct transcript *transcript, bool flag_t, bool flag_d, char *title) { return FAIL; }

static enum result transcript_add_class(struct transcript *transcript /* FINISH SUMMARY */) { return FAIL; }

enum result parser_execute(int argc, char **argv, struct transcript *transcript, enum state_type *state) {
    uint8_t i, j;
    switch (*state) {
    case ENTRY:
        if (string_equals(argv[1], "list") && argc == 2) {      
            return entry_list(transcript);
        } else if (string_equals(argv[1], "open")) {
            bool flag_t = false, flag_d = false;
            for (i = 2; i < argc; ++i) {
                if (argv[i][0] != '-') break;
                for (j = 1; true; ++j) {
                    if (argv[i][j] == 't') flag_t = true;
                    else if (argv[i][j] == 'd') flag_d = true;
                    else if (argv[i][j] == '\0') break;
                    else goto fail;
                }
            }

            if (i == argc - 1) { 
                *state = TRANSCRIPT;
                return entry_open(transcript, flag_t, flag_d, argv[i]);
            }
        }
        
        goto fail;
    case TRANSCRIPT:
        if (string_equals(argv[1], "addc")) {

        }
    }

    fail: return FAIL;
}