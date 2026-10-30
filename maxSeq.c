#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t maxSeq(int* array, size_t n){
    if(n == 0){
        return 0;
    }
    int ans = 0; int temp = 0; int min_int = INT_MIN;
    for(int i = 0; i < n; i++){
        if(array[i] > min_int){
            temp++; min_int = array[i];
        }else{
            if(temp > ans){
                ans = temp;
            }
            temp = 1; min_int = array[i];
        }
    }
    if(temp > ans){
        ans = temp;
    }
    return ans;
}

int main(){
    printf("%zu", maxSeq((int[]){1,2,1,2,3}, 5));
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
    printf("yay");
    return EXIT_SUCCESS;
}


