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
    return ((subject[0] - 0x40) << 26)
            + ((subject[2] - 0x40) << 21)
            + ((subject[3] - 0x40) << 16)
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
    return course->grade * course->credits / 10.;
}

float course_max_grade_points(struct course *course) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    return A * course->credits / 10.;
}

char *course_alloc_details(struct course *course) {
    if (course == NULL) exit(EXIT_ALLOC_FAIL);
    char *out = malloc(MAX_LEN * sizeof(char));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);

    sprintf_s(out, MAX_LEN, "s>[%c] %s%d: (%d) $%s", 
        course->completed ? 'x' : '_',
        course->subject,
        course->credits,
        course->id,
        course->title,
        course->grade);
    return out;
}