#include <stdlib.h>
#include <time.h>

#include "../globals.h"
#include "transcript.h"

static const uint8_t DEFAULT_MAX_COURSES = 10;

static struct semester *semester_alloc() {
    struct semester *out = malloc(sizeof(struct semester));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);
    out->course_count = 0;
    out->courses = malloc(DEFAULT_MAX_COURSES * sizeof(struct course *));
    if (out->courses == NULL) exit(EXIT_ALLOC_FAIL);
    return out;
}

static void semester_free(struct semester *semester) {
    uint8_t i;
    for (i = 0; i < semester->course_count; ++i) {
        course_free(semester->courses[i]);
    }

    free(semester->courses);
    free(semester);
}

static void semester_add_course(struct semester *semester, struct course *course) {
    if (semester == NULL || course == NULL) exit(EXIT_ALLOC_FAIL);
    semester->courses[semester->course_count++] = course;
}

static void semester_rem_course(struct semester *semester, uint32_t course_uid) {
    if (semester == NULL) exit(EXIT_ALLOC_FAIL);
    
    uint8_t i, j;
    for (i = 0; i < semester->course_count; ++i) {
        if (semester->courses[i]->uid == course_uid) {
            course_free(semester->courses[i]);
        }
    }

    while (i < semester->course_count - 1) {
        semester->courses[i] = semester->courses[i + 1];
    }
}

struct transcript *transcript_alloc() {

}

void transcript_free(struct transcript *transcript) {
    
}

void transcript_add_transfer(struct transcript *transcript, struct course *course) {

}

void transcript_rem_transfer(struct transcript *transcript, uint32_t course_uid) {

}

void transcript_add_semester(struct transcript *transcript) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

}

void transcript_rem_semester(struct transcript *transcript) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

}

void transcript_add_course(struct transcript *transcript, uint8_t semester, struct course *course) {

}

void transcript_rem_course(struct transcript *transcript, uint8_t semester, uint32_t course_uid) {

}

void transcript_change_grade(struct transcript *transcript, uint8_t semester, uint32_t course_uid, enum grade grade) {

}