#include <stdint.h>

#include "../globals.h"

extern const uint8_t MAX_LEN;
extern const char DELIMITER;

/**
 * Each line must begin with "x>", where x is an the alignment character;
 * 'l' - left alignment; 
 * 'c' - center alignment (left-favoring); 
 * 'r' - right alignment; 
 * 's' - split alignment (switch from left to right alignment on delimiter '$';
 * 'x' - triple alignment (switch l->c->r alignment on delimiter '$')
 * 'f' - fill line (first character on edges, second character fills space)
 * Upon fail, parameter <code>fail<\code> is set to the failing line number.
 */
enum result print(const char *text, int *fail);