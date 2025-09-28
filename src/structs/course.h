#include <stdbool.h>
#include <stdint.h>

enum grade {
    UNGRADED = -1,
    GRADE_A  = 40,
    GRADE_Am = 37,
    GRADE_Bp = 33,
    GRADE_B  = 30,
    GRADE_Bm = 27,
    GRADE_Cp = 23,
    GRADE_C  = 20,
    GRADE_Cm = 17,
    GRADE_Dp = 13,
    GRADE_D  = 10,
    GRADE_F  = 0
};

struct course {
    char *subject;
    uint16_t id;
    uint32_t uid;
    char *title;
    uint8_t credits;

    enum grade grade;
    bool completed;
};

/**
 * Generate a unique id for a course. The subject field should be a string of no fewer
 * than 2 and no more than 4 characters, all of which should be uppercase letters
 */
uint32_t course_generate_uid(char *subject, uint16_t id);

/**
 * Allocate a new course struct
 */
struct course *course_alloc(char *subject, uint16_t id, char *title, uint8_t credits);

/**
 * Free a course struct
 */
void course_free(struct course *course);

/**
 * Input a grade for a course
 */
void course_regrade(struct course *course, enum grade grade);

/**
 * Mark a course completed
 */
void course_mark_completed(struct course *course, bool completed);

/**
 * Get the current grade point value of this course, -1 if no grade.
 */
float course_grade_points(struct course *course);

/**
 * Get the maximum possible grade point value of this course
 */
float course_max_grade_points(struct course *course);

/**
 * String representation for a course
 */
char *course_alloc_details(struct course *course);