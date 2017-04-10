#ifndef RESULTS_H
#define RESULTS_H

#define MSG_SUCCESS  "success"

typedef struct {
    const char* name;
    int prob;
    int count;
} detected_object;

typedef struct {
    const char* res;
    detected_object* objects;
    int last;
} detection_result;


void print_error_results(const char* message);
detection_result* new_detection_results(const char* message, int max_size);
void detection_result_add(detection_result* dr, const char* name, int prob);
void print_results(detection_result* dr);
void free_results(detection_result* dr);

#endif /* RESULTS_H */

