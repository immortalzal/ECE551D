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

void freecat_t(category_t* cat){
    if(cat == NULL){
        return;
    }
    for(int i = 0; i < cat -> n_words; i++){
        free(cat -> words[i]);
    }
    free(cat -> words);
    free(cat);
}

catarray_t* step2(char* filename){
    if(filename == NULL){
        fprintf(stderr, "filename is NULL");
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(filename, "r");
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
    fclose(f);
    return cat;
}

int main(int argc, char** argv){
    int buff = 0;
    if(argc < 3 || argc > 4){
        fprintf(stderr, "wrong number of args");
        exit(EXIT_FAILURE);
    }
    if(argc == 4 && strcmp("-n", argv[1]) != 0){
        fprintf(stderr, "wrong format");
        exit(EXIT_FAILURE);
    }
    if(argc == 4){
        buff++;
    }
    catarray_t* cat = step2(argv[1 + buff]);
    if(argv[2 + buff] == NULL){
        fprintf(stderr, "filename 2 is NULL");
        freecat(cat);
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(argv[2 + buff], "r");
    if(f == NULL){
        fprintf(stderr, "f is NULL");
        freecat(cat);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t length = 0; int underscore_count;
    char* temp = NULL; 
    category_t* word_array = malloc(sizeof(*word_array));
    word_array -> name = NULL;
    word_array -> n_words = 0;
    word_array -> words = NULL;
    while(getline(&line, &length, f) >= 0){
        int str_len = 0; underscore_count = 0; int i = 0;
        while(line[i] != '\0' && line[i] != '\n'){
            if(line[i] != '_'){
                if(underscore_count % 2 == 0){
                    printf("%c", line[i]);
                }else{
                    temp = realloc(temp, (str_len + 1) * sizeof(*temp));
                    temp[str_len] = line[i];
                    str_len++;
                }
            }else{
                underscore_count++;
                if(underscore_count % 2 == 0){
                    int flag_1 = 0; int flag_2 = 0;
                    temp = realloc(temp, (str_len + 1) * sizeof(*temp));
                    temp[str_len] = '\0';
                    for(int i = 0; i < str_len; i++){
                        if(!(temp[i] >= '0' && temp[i] <= '9')){
                            flag_1 = 1;
                        }
                    }
                    if(flag_1 == 0 && atoi(temp) <= 0){
                        flag_1 = 1;
                    }
                    if(flag_1 == 0){
                        int val = atoi(temp);
                        if(word_array -> n_words < val){
                            fprintf(stderr, "index out of bounds");
                            free(temp);
                            free(line);
                            freecat_t(word_array);
                            freecat(cat);
                            exit(EXIT_FAILURE);
                        }
                        printf("%s", word_array -> words[word_array -> n_words - val]);
                        word_array -> words = realloc(word_array -> words, (word_array -> n_words + 1) * sizeof(*word_array -> words));
                        word_array -> words[word_array -> n_words] = strdup(word_array -> words[word_array -> n_words - val]);
                        word_array -> n_words++;
                    }else{
                        for(int j = 0; j < cat -> n; j++){
                            if(strcmp(cat -> arr[j].name, temp) == 0){
                                flag_2 = 1;
                            }
                        }
                        if(flag_2 == 0){
                            fprintf(stderr, "cannot find category in cat");
                            free(temp);
                            free(line);
                            freecat_t(word_array);
                            freecat(cat);
                            exit(EXIT_FAILURE);
                        }else{
                            char* string = strdup(chooseWord(temp, cat));
                            printf("%s", string);
                            if(buff == 1){
                                for(int i = 0; i < cat -> n; i++){
                                    if(strcmp(cat -> arr[i].name, temp) == 0){
                                        for(int j = 0; j < cat -> arr[i].n_words; j++){
                                            if(strcmp(string, cat -> arr[i].words[j]) == 0){
                                                free(cat -> arr[i].words[j]);
                                                if(j < cat -> arr[i].n_words - 1){
                                                    cat -> arr[i].words[j] = cat -> arr[i].words[cat -> arr[i].n_words - 1];
                                                }
                                                break;
                                            }
                                        }
                                        cat -> arr[i].n_words--;
                                        if(cat -> arr[i].n_words <= 0){
                                            free(cat -> arr[i].words);
                                            cat -> arr[i].words = NULL;
                                        }else{
                                            cat -> arr[i].words = realloc(cat -> arr[i].words, (cat -> arr[i].n_words) * sizeof(*cat -> arr[i].words));
                                        }
                                    }
                                }
                            }
                            word_array -> words = realloc(word_array -> words, (word_array -> n_words + 1) * sizeof(*word_array -> words));
                            word_array -> words[word_array -> n_words] = strdup(string);
                            word_array -> n_words++;
                            free(string);
                        }
                    }
                    str_len = 0;
                }
            }
            i++;
        }
        if(underscore_count % 2 == 1){
            free(temp);
            free(line);
            freecat_t(word_array);
            freecat(cat);
            fprintf(stderr, "weird underscore count");
            exit(EXIT_FAILURE);
        }
        printf("\n");
    }
    free(temp);
    free(line);
    freecat_t(word_array);
    freecat(cat);
    fclose(f);
    return EXIT_SUCCESS;
}