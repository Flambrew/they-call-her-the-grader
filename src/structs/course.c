#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../utils/printer.h"
#include "course.h"

uint32_t calculate_uid(char *subject, uint16_t id) {
    uint8_t i, flag;
    char subj[4];
    for (i = flag = 0; i < 4; ++i) {
        if (subject[i] == '\0') {
            flag = 1;
        }
        subj[i] = '@';
    }
    return ((subj[0] - 0x40) << 26)
            + ((subj[2] - 0x40) << 21)
            + ((subj[3] - 0x40) << 16)
            + id;
}

struct course *course_alloc(char *subject, uint16_t id, char *title, uint8_t credits) {
    struct course *out = malloc(sizeof(struct course));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);
    out->subject = subject;
    out->id = id;
    out->uid = calculate_uid(subject, id);
    out->title = title;
    out->credits = credits;
    out->grade = UNGRADED;
    out->completed = false;
    return out;
}

void course_free(struct course *course) {
    free(course);
}

void course_regrade(struct course *course, enum grade grade) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    course->grade = grade;
}

void course_mark_completed(struct course *course, bool completed) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    course->completed = completed;
}

float course_grade_points(struct course *course) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    if (course->grade == UNGRADED) return -1;
    return course->grade * course->credits / 10.;
}

float course_max_grade_points(struct course *course) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    return GRADE_A * course->credits / 10.;
}

static const char *grade_to_str(enum grade grade) {
    switch (grade) {
        case GRADE_A:  return "A";
        case GRADE_Am: return "A-";
        case GRADE_Bp: return "B+";
        case GRADE_B:  return "B";
        case GRADE_Bm: return "B-";
        case GRADE_Cp: return "C+";
        case GRADE_C:  return "C";
        case GRADE_Cm: return "C-";
        case GRADE_Dp: return "D+";
        case GRADE_D:  return "D";
        case GRADE_F:  return "F";
        case UNGRADED: return "-";
        default:       return "x";
    }
}

char *course_alloc_details(struct course *course) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    char *out = malloc(MAX_LEN * sizeof(char));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);

    sprintf(out, "s>[%c] %s%d: %s$%s (%dcr)", 
        course->completed ? 'x' : '_',
        course->subject,
        course->id,
        course->title,
        grade_to_str(course->grade),
        course->credits);
    return out;
}