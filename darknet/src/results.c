#include "results.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

detection_result* new_detection_results(const char* message, int max_size) {
    detection_result* dr = (detection_result*) malloc(sizeof (detection_result));
    dr->res = message;
    if (max_size > 0) {
        dr->objects = malloc(sizeof (detected_object) * max_size);
    } else {
        dr->objects = NULL;
    }
    dr->last = 0;
    return dr;
}

void detection_result_add(detection_result* dr, const char* name, int prob) {
    if (dr == NULL) {
        return;
    }
    int i = 0;
    for (; i < dr->last; i++) {
        if (strcmp(dr->objects[i].name, name) == 0) {
            dr->objects[i].count++;
            if (prob > dr->objects[i].prob) {
                dr->objects[i].prob = prob;
            }
            return;
        }
    }
    dr->objects[dr->last].name = name;
    dr->objects[dr->last].count = 1;
    dr->objects[dr->last].prob = prob;
    dr->last++;
}

/*
 { "res": "success",
 * "objects": [{"name":"obj_name","min_prob":50,"count":5},...]
 */

void print_results(detection_result* dr) {
    if (dr == NULL) {
        return;
    }
    printf("{");
    printf("\"res\":\"%s\",", dr->res);
    printf("\"objects\": [");
    int i = 0;
    for (; i < dr->last; i++) {
        printf("{");
        printf("\"name\":\"%s\",", dr->objects[i].name);
        printf("\"count\":%d,", dr->objects[i].count);
        printf("\"prob\":%d", dr->objects[i].prob);
        printf("}");
        if (i < dr->last - 1) {
            printf(",");
        }
    }
    printf("]");
    printf("}");
    fflush(stdout);
}

void free_results(detection_result* dr) {
    if (dr == NULL) {
        return;
    }
    if (dr->objects != NULL) {
        free(dr->objects);
    }
    free(dr);
    dr = NULL;
}

void print_error_results(const char* message) {
    detection_result* dr = new_detection_results(message, 0);
    print_results(dr);
    free_results(dr);
}