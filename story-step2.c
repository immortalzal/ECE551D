#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"

void freecat(catarray_t* cat){
    if(cat == NULL){
        return;
    }
    for(int i = 0; i < cat -> n; i++){
        for(int j = 0; j < cat -> arr[i].n_words; j++){
            free(cat -> arr[i].words[j]);
        }
        free(cat -> arr[i].words);
        free(cat -> arr[i].name);
    }
    free(cat -> arr);
    free(cat);
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "wrong number of args");
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
        fprintf(stderr, "f is NULL");
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t length = 0; int colon_count = 0;
    catarray_t* cat = malloc(sizeof(*cat));
    cat -> arr = NULL; cat -> n = 0; int flag, flag_2;
    while(getline(&line, &length, f) >= 0){
        char* category = NULL;
        char* word = NULL;
        int i = 0; colon_count = 0;
        int category_length = 0;
        int word_length = 0; flag = 0; flag_2 = 0;
        while(line[i] != '\0' && line[i] != '\n'){
            if(line[i] == ':' && colon_count == 0){
                colon_count++;
            }else{
                if(colon_count == 0){
                    category = realloc(category, (category_length + 1) * sizeof(*category));
                    category[category_length] = line[i];
                    category_length++;
                }else{
                    word = realloc(word, (word_length + 1) * sizeof(*word));
                    word[word_length] = line[i];
                    word_length++;
                }
            }
            i++;
        }
        if(colon_count < 1){
            free(category);
            free(word);
            free(line);
            freecat(cat);
            fprintf(stderr, "wrong formatting: colon");
            exit(EXIT_FAILURE);
        }
        category = realloc(category, (category_length + 1) * sizeof(*category));
        word = realloc(word, (word_length + 1) * sizeof(*word));
        category[category_length] = '\0';
        word[word_length] = '\0';
        for(int i = 0; i < cat -> n; i++){
            if(strcmp(category, cat -> arr[i].name) == 0){
                flag = 1;
                if(flag_2 == 0){
                    cat -> arr[i].words = realloc(cat -> arr[i].words, (cat -> arr[i].n_words + 1) * sizeof(*cat -> arr[i].words));
                    cat -> arr[i].words[cat -> arr[i].n_words] = strdup(word);
                    cat -> arr[i].n_words++;
                }
                break;
            }
        }
        if(flag == 0){
            cat -> arr = realloc(cat -> arr, ((cat -> n) + 1) * sizeof(*cat -> arr));
            cat -> arr[cat -> n].name = strdup(category);
            cat -> arr[cat -> n].n_words = 1;
            cat -> arr[cat -> n].words = malloc(sizeof(*(cat -> arr[cat -> n].words)));
            cat -> arr[cat -> n].words[0] = strdup(word);
            (cat -> n)++;
        }
        free(category);
        free(word);
    }
    free(line);
    printWords(cat);
    freecat(cat);
    fclose(f);
}