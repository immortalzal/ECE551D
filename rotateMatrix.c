#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv){
    char ans[10][10];
    char* buff;
    char temp[15];
    if(argc != 2){
        fprintf(stderr, "err, variables for argc\n");
        exit(EXIT_FAILURE);
    }
    const char* input_file = argv[1];
    FILE* f = fopen(input_file, "r");
    if(f == NULL){
        fprintf(stderr, "err, f = NULL\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i <= 10; i++){
        char* tmp = fgets(temp, 12, f);
        if(tmp != NULL && i < 10){
            buff = strchr(temp, '\n');
            if(buff == NULL || buff - temp != 10){
                fprintf(stderr, "err, buff = NULL or buff - temp == %ld\n", buff - temp);
                exit(EXIT_FAILURE);
            }else{
                for(int j = 0; j < 10; j++){
                    ans[j][9 - i] = temp[j];
                }
            }
        }else if((tmp == NULL && i < 10) || (tmp != NULL && i == 10)){
            fprintf(stderr, "err, fgets is NULL\n");
            exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            printf("%c", ans[i][j]);
        }
        printf("\n");
    }
}
