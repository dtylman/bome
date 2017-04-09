/* 
 * File:   bome.c
 * Author: danny
 *
 * Created on April 9, 2017, 12:58 PM
 */

#include "utils.h"
#include "option_list.h"
#include "data.h"
#include "network.h"
#include "parser.h"
#include "region_layer.h"
#include <limits.h>

#define DATA_CFG "coco.data"
#define WEIGHT_FILE "yolo.weights"
#define CONFIG_FILE "yolo.cfg"
#define NAMES_LIST "coco.names"


// ./darknet detect cfg/yolo.cfg yolo.weights data/dog.jpg

void print_detections(int num, float thresh, float **probs, char **names, int classes) {
    printf("[");
    int items = 0;
    int i;
    for (i = 0; i < num; ++i) {
        int class = max_index(probs[i], classes);
        float prob = probs[i][class];
        if (prob > thresh) {
            if (items>0){
                printf(",");
            }
            items++;
            //{"name":"lala","prob":30}            
            printf("{\"name\":\"%s\",\"prob\": %.0f}", names[class], prob * 100);            
        }
    }
    printf("]\n");
}

void yolo_detect(float thresh, float hier_thresh) {
    list *options = read_data_cfg(DATA_CFG);
    char *name_list = option_find_str(options, "names", NAMES_LIST);
    char **names = get_labels(name_list);
    network net = parse_network_cfg(CONFIG_FILE);
    load_weights(&net, WEIGHT_FILE);
    set_batch_network(&net, 1);
    srand(2222222);
    int j;
    float nms = .4;
    char buf[PATH_MAX];
    char* input = buf;
    while (1) {
        input = fgets(input, PATH_MAX, stdin);
        if (!input) {
            continue;
        }
        strip(input);
        image im = load_image_color(input, 0, 0);
        if (im.data==NULL){ //empty image
            free_image(im);          
            continue;
        }
        image sized = letterbox_image(im, net.w, net.h);
        //image sized = resize_image(im, net.w, net.h);
        //image sized2 = resize_max(im, net.w);
        //image sized = crop_image(sized2, -((net.w - sized2.w)/2), -((net.h - sized2.h)/2), net.w, net.h);
        //resize_network(&net, sized.w, sized.h);
        layer l = net.layers[net.n - 1];

        box *boxes = calloc(l.w * l.h * l.n, sizeof (box));
        float **probs = calloc(l.w * l.h * l.n, sizeof (float *));
        for (j = 0; j < l.w * l.h * l.n; ++j) {
            probs[j] = calloc(l.classes + 1, sizeof (float *));
        }

        float *X = sized.data;
        network_predict(net, X);
        get_region_boxes(l, 1, 1, thresh, probs, boxes, 0, 0, hier_thresh);
        if (l.softmax_tree && nms) {
            do_nms_obj(boxes, probs, l.w * l.h * l.n, l.classes, nms);
        }
        if (nms) {
            do_nms_sort(boxes, probs, l.w * l.h * l.n, l.classes, nms);
        }
        print_detections(l.w * l.h * l.n, thresh, probs, names, l.classes);
        fflush(stdout);
        //       draw_detections(sized, l.w*l.h*l.n, thresh, boxes, probs, names, alphabet, l.classes);
        //       save_image(sized, "predictions");
        //       show_image(sized, "predictions");

        free_image(im);
        free_image(sized);
        free(boxes);
        free_ptrs((void **) probs, l.w * l.h * l.n);
    }
}

int main(int argc, char** argv) {
    float thresh = find_float_arg(argc, argv, "-thresh", .24);
    yolo_detect(thresh, .5);
    return 0;
}

