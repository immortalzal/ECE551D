#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
    counts_t* name_arr = malloc(sizeof(*name_arr));
    name_arr -> arr = NULL;
    name_arr -> length = 0;
    name_arr -> unknowns = 0;
    return name_arr;
  
}
void addCount(counts_t * c, const char * name) {
    if(name == NULL){
        c -> unknowns++;
    }else{
        for(int i = 0; i < c -> length; i++){
            if(strcmp(c -> arr[i].string, name) == 0){
                c -> arr[i].count++;
                return;
            }
        }
        c -> arr = realloc(c -> arr, ((c -> length) + 1) * sizeof(one_count_t));
        if(c -> arr == NULL){
            for(int i = 0; i < c -> length; i++){
                free(c -> arr[i].string);
            }
        }else{
            c -> arr[c -> length].string = strdup(name);
            c -> arr[c -> length].count = 1;
            c -> length++;
            }
        }
    }   
}
void printCounts(counts_t * c, FILE * outFile) {
    if(outFile == NULL || c == NULL){
        return;
    }
    for(int i = 0; i < c -> length; i++){
       fprintf(outFile, "%s: %d\n", c -> arr[i].string, c -> arr[i].count);
    }
    if(c -> unknowns > 0){
        fprintf(outFile, "<unknown>: %d\n", c -> unknowns);
    }
}

void freeCounts(counts_t * c) {
    if(c == NULL){
        return;
    }
    for(int i = 0; i < c -> length; i++){
        free(c -> arr[i].string);
    }
    free(c -> arr);
    free(c);
}
