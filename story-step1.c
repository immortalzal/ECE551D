#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"

int main(int argc, char ** argv){
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
    size_t length = 0; int underscore_count;
    char* temp = NULL; 
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
                    printf("%s", chooseWord(temp, NULL));
                    str_len = 0;
                }
            }
            i++;
        }
        if(underscore_count % 2 == 1){
            fprintf(stderr, "weird underscore count");
            exit(EXIT_FAILURE);
        }
        printf("\n");
    }
    free(temp);
    free(line);
    fclose(f);
    return EXIT_SUCCESS;
}