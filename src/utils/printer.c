#include <stdint.h>
#include <stdio.h>

#include "printer.h"

static const uint8_t TAB_LEN = 8;
static const uint8_t FORMAT = 2;
static const uint8_t TERMINATOR = 1;

const uint8_t MAX_LEN = FORMAT + TERMINATOR + MAX_CHARS_PER_LINE;
const char DELIMITER = '$';

static enum result ln_print(const char *text, const int len) {
    if (len < FORMAT + TERMINATOR || text[1] != '>') {
        return FAIL;
    }

    uint8_t i, pad;
    char pad_str[MAX_CHARS_PER_LINE];
    switch(text[0]) {
        case 'l': pad = 0; break;
        case 'c': pad = (MAX_LEN - len) / 2; break;
        case 'r': pad = MAX_LEN - len; break;
        case 's': {
            char left[MAX_CHARS_PER_LINE], right[MAX_CHARS_PER_LINE];
            uint8_t j = FORMAT, l_len = 0, r_len = 0;
            for (i = 0; text[j] != DELIMITER; ++i, ++j, ++l_len) {
                if (j == len) return FAIL;
                left[i] = text[j];
            }
            left[i] = '\0';
            ++j;

            for (i = 0; text[j] != '\0'; ++i, ++j, ++r_len) {
                if (j == len) return FAIL;
                right[i] = text[j];
            }
            right[i] = '\0';

            pad = MAX_CHARS_PER_LINE - l_len - r_len;
            for (i = 0; i < pad; ++i) {
                pad_str[i] = ' ';
            }

            pad_str[i] = '\0';
            printf("%s%s%s\n", left, pad_str, right);
            return PASS;
        }
        case 'x': {
            char left[MAX_CHARS_PER_LINE], center[MAX_CHARS_PER_LINE], right[MAX_CHARS_PER_LINE], pad_str_b[MAX_CHARS_PER_LINE];
            uint8_t j = FORMAT, l_len = 0, c_len = 0, r_len = 0, pad_b;
            for (i = 0; text[j] != DELIMITER; ++i, ++j, ++l_len) {
                if (j == len) return FAIL;
                left[i] = text[j];
            }
            left[i] = '\0';
            ++j;

            for (i = 0; text[j] != DELIMITER; ++i, ++j, ++c_len) {
                if (j == len) return FAIL;
                center[i] = text[j];
            }
            center[i] = '\0';
            ++j;

            for (i = 0; text[j] != '\0'; ++i, ++j, ++r_len) {
                if (j == len) return FAIL;
                right[i] = text[j];
            }
            right[i] = '\0';

            pad = (MAX_CHARS_PER_LINE - l_len - c_len - r_len) / 2;
            pad_b = (MAX_CHARS_PER_LINE - l_len - c_len - r_len) - pad;

            for (i = 0; i < pad; ++i) 
                pad_str[i] = ' ';
            pad_str[i] = '\0';
            for (i = 0; i < pad_b; ++i) 
                pad_str_b[i] = ' ';
            pad_str_b[i] = '\0';

            printf("%s%s%s%s%s\n", left, pad_str, center, pad_str_b, right);
            return PASS;
        }
        case 'f':
            if (len != FORMAT + TERMINATOR + 2) 
                return FAIL;
            for (i = 0; i < MAX_CHARS_PER_LINE - 2; ++i) 
                pad_str[i] = text[3];
            printf("%c%s%c\n", text[2], pad_str, text[2]);
            return PASS;
        default:
            return FAIL;
    }
            
    i = 0;
    while (pad > 0) {
        pad_str[i++] = ' ';
        --pad;
    }

    pad_str[i] = '\0';
    printf("%s%s\n", pad_str, text + FORMAT);
    return PASS;
}

enum result print(const char *text, int *fail) {
    uint32_t i, j, ct;
    char line[MAX_LEN];

    i = j = ct = 0;
    do {
        if (j >= MAX_LEN) {
            *fail = ct;
            return FAIL;
        } else if (text[i] == '\0' || text[i] == '\n') {
            line[j++] = '\0';
            if (ln_print(line, j) == FAIL)
                return FAIL;
            j = 0;
            ++ct;
        } else if (text[i] == '\t') {
            uint8_t pos = (j + TAB_LEN) - (j + TAB_LEN) % TAB_LEN;
            while (j < pos) {
                line[j++] = ' ';
            }
        } else {
            line[j++] = text[i];
        }
    } while (text[i++] != '\0');

    return PASS;
}