#include <stdlib.h>

#include "transcript.h"

static const uint8_t MAX_COURSES = 10;
static const uint8_t MAX_SEMESTERS = 20;

static struct semester *semester_alloc() {
    struct semester *out = malloc(sizeof(struct semester));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);
    out->course_count = 0;
    out->courses = malloc(MAX_COURSES * sizeof(struct course *));
    if (out->courses == NULL) exit(EXIT_ALLOC_FAIL);
    return out;
}

static void semester_free(struct semester *semester) {
    if (semester == NULL) exit(EXIT_ALLOC_FAIL);

    uint8_t i;
    for (i = 0; i < semester->course_count; ++i) {
        course_free(semester->courses[i]);
    }

    free(semester->courses);
    free(semester);
}

static enum result semester_add_course(struct semester *semester, struct course *course) {
    if (semester == NULL || course == NULL) exit(EXIT_ALLOC_FAIL);
    if (semester->course_count == MAX_COURSES) return FAIL;

    semester->courses[semester->course_count++] = course;
    return PASS;
}

static enum result semester_rem_course(struct semester *semester, uint32_t course_uid) {
    if (semester == NULL) exit(EXIT_ALLOC_FAIL);
    
    uint8_t i;
    for (i = 0; i < semester->course_count; ++i) {
        if (semester->courses[i]->uid == course_uid) {
            course_free(semester->courses[i]);
            break;
        }
    }

    if (i == semester->course_count) {
        return FAIL;
    }

    while (i < semester->course_count - 1) {
        semester->courses[i] = semester->courses[i + 1];
    }

    --semester->course_count;
    return PASS;
}

static enum result semester_regrade(struct semester *semester, uint32_t course_uid, enum grade grade) {
    if (semester == NULL) exit(EXIT_ALLOC_FAIL);
    
    uint8_t i;
    for (i = 0; i < semester->course_count; ++i) {
        if (semester->courses[i]->uid == course_uid) {
            course_regrade(semester->courses[i], grade);
            return PASS;
        }
    }

    return FAIL;
}

struct transcript *transcript_alloc() {
    struct transcript *out = malloc(sizeof(struct transcript));
    if (out == NULL) exit(EXIT_ALLOC_FAIL);
    out->current_semester = -1;
    out->semester_count = 0;
    out->semesters = malloc(sizeof(struct semester *) * MAX_SEMESTERS);
    if (out->semesters == NULL) exit(EXIT_ALLOC_FAIL);
    out->transfer_course_count = 0;
    out->transfer_course_max = MAX_COURSES;
    out->transfer_courses = malloc(sizeof(struct course *) * MAX_COURSES);
    if (out->transfer_courses == NULL) exit(EXIT_ALLOC_FAIL);
    return out;
}

void transcript_free(struct transcript *transcript) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

    uint8_t i;
    for (i = 0; i < transcript->semester_count; ++i) {
        semester_free(transcript->semesters[i]);
    }

    for (i = 0; i < transcript->transfer_course_count; ++i) {
        course_free(transcript->transfer_courses[i]);
    }

    free(transcript->semesters);
    free(transcript->transfer_courses);
    free(transcript);
}

void transcript_add_transfer(struct transcript *transcript, struct course *course) {
    if (transcript == NULL || course == NULL) exit(EXIT_ALLOC_FAIL);

    if (transcript->transfer_course_count == transcript->transfer_course_max) {
        transcript->transfer_courses = realloc(transcript->transfer_courses, 
                sizeof(struct course *) * (transcript->transfer_course_max *= 2));
    }

    if (transcript->transfer_courses == NULL) exit(EXIT_ALLOC_FAIL);

    transcript->transfer_courses[transcript->transfer_course_count++] = course;
}

enum result transcript_rem_transfer(struct transcript *transcript, uint32_t course_uid) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

    uint8_t i;
    for (i = 0; i < transcript->transfer_course_count; ++i) {
        if (transcript->transfer_courses[i]->uid == course_uid) {
            course_free(transcript->transfer_courses[i]);
            break;
        }
    }

    if (i == transcript->transfer_course_count) return FAIL;

    while (i < transcript->transfer_course_count - 1) {
        transcript->transfer_courses[i] = transcript->transfer_courses[i + 1];
    }

    --transcript->transfer_course_count;
    return PASS;
}

void transcript_add_semester(struct transcript *transcript) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

    transcript->semesters[transcript->semester_count++] = semester_alloc();
}

void transcript_rem_semester(struct transcript *transcript) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

    semester_free(transcript->semesters[--transcript->semester_count]);
}

void transcript_add_course(struct transcript *transcript, int8_t semester, struct course *course) {
    if (transcript == NULL || course == NULL) exit(EXIT_ALLOC_FAIL);
    if (semester == -1) semester = transcript->current_semester;

    semester_add_course(transcript->semesters[semester], course);
}

enum result transcript_rem_course(struct transcript *transcript, int8_t semester, uint32_t course_uid) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);
    if (semester != -1) semester = transcript->current_semester;
    
    return semester_rem_course(transcript->semesters[semester], course_uid);
}

enum result transcript_regrade(struct transcript *transcript, int8_t semester, uint32_t course_uid, enum grade grade) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);
    if (semester != -1) semester = transcript->current_semester;

    return semester_regrade(transcript->semesters[semester], course_uid, grade);
}

void transcript_set_semester(struct transcript *transcript, int8_t current_semester) {
    if (transcript == NULL) exit(EXIT_ALLOC_FAIL);

    transcript->current_semester = current_semester;
}