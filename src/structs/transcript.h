#include <stdint.h>

#include "../globals.h"
#include "course.h"

struct semester {
    uint8_t course_count;
    struct course **courses;
};

struct transcript {
    uint8_t transfer_course_max;
    uint8_t transfer_course_count;
    struct course **transfer_courses;

    uint8_t semester_count;
    uint8_t current_semester;
    struct semester **semesters;
};

struct transcript *transcript_alloc();
void transcript_free(struct transcript *transcript);

void transcript_add_transfer(struct transcript *transcript, struct course *course);
enum result transcript_rem_transfer(struct transcript *transcript, uint32_t course_uid);

void transcript_add_semester(struct transcript *transcript);
void transcript_rem_semester(struct transcript *transcript);

void transcript_add_course(struct transcript *transcript, int8_t semester, struct course *course);
enum result transcript_rem_course(struct transcript *transcript, int8_t semester, uint32_t course_uid);

enum result transcript_regrade(struct transcript *transcript, int8_t semester, uint32_t course_uid, enum grade grade);
void transcript_set_semester(struct transcript *transcript, int8_t current_semester);