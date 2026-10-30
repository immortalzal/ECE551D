#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int* array, size_t n);

int main(){
    if(maxSeq((int[]){1,1,1,1}, 4) != 1){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1,2,1,2,3}, 5) != 3){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1,2,3,1,2}, 5) != 3){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1,2,3,4,5,6}, 5) != 5){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){5,4,3,2,1}, 5) != 1){
        return EXIT_FAILURE;
    }
    if(maxSeq(NULL, 0) != 0){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1,2,2,3,3}, 5) != 2){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){-3, -2, -2, -1, -1}, 5) != 2){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){2,1,2,1,2}, 5) != 2){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1}, 1) != 1){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1,2,3}, 0) != 0){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){-1,0,-1, 0}, 4) != 2){
        return EXIT_FAILURE;
    }
    if(maxSeq((int[]){1, -1}, 2) != 1){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
