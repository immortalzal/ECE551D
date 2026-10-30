#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
    int count = 0; int equal_count = 0;
    char* line = NULL; int equal_ind;
    size_t length = 0;
    FILE *f = fopen(fname, "r");
    if(f == NULL){
        fprintf(stderr, "fileread failed\n");
        exit(EXIT_FAILURE);
    }
    kvarray_t* kvarray = malloc(sizeof(kvarray_t));
    if(kvarray == NULL){
        fprintf(stderr, "malloc kvarray failed\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    kvarray -> array = NULL;
    kvarray -> length = 0;
    while(getline(&line, &length, f) >= 0){
        equal_count = 0;
        if(strlen(line) - 1 >= 0 && line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        kvpair_t* temp = realloc(kvarray -> array, (count + 1) * sizeof(kvpair_t));
        if(temp == NULL){
            fprintf(stderr, "fileread failed");
            free(line);
            freeKVs(kvarray);
            exit(EXIT_FAILURE);
        }
        kvarray -> array = temp;
        for(int i = 0; i < strlen(line); i++){
            if(line[i] == '=' && equal_count == 0){
                equal_count++; equal_ind = i;
                kvarray -> array[count].key = strndup(line, equal_ind);
            }
        }
        if(equal_count == 0){
            freeKVs(kvarray);
            return NULL;
        }
        kvarray -> array[count].value = strdup(line + equal_ind + 1);
        count++;
    }
    kvarray -> length = count;
    free(line);
    fclose(f);
    return kvarray;
}

void freeKVs(kvarray_t * pairs) {
    if(pairs == NULL){
        return;
    }
    if(pairs -> array != NULL){
        for(int i = 0; i < pairs -> length; i++){
            free(pairs -> array[i].key);
            free(pairs -> array[i].value);
        }
        free(pairs -> array);
    }
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs -> length; i++){
    printf("key = '%s' value = '%s'\n", pairs -> array[i].key, pairs -> array[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    for(int i = 0; i < pairs -> length; i++){
        if(strcmp(pairs -> array[i].key, key) == 0){
            return pairs -> array[i].value;
        }
    }
    return NULL;
}
