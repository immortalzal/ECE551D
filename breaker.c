#include <stdlib.h>
#include <stdio.h>

int arrayMax(int * array, int n) {
    if(n == 0){
        return -1;
    }
    int ans = -2147483648;
    int index = -1;
    for(int i = 0; i < n; i++){
        if(array[i] > ans){
            ans = array[i];
            index = i;
        }
    }
    return index;
}

int main(int argc, char ** argv){
    int arr[26] = {0};
    int c;
    if(argc != 2){
        fprintf(stderr, "err");
        exit(EXIT_FAILURE);
    }
    const char* input_file = argv[1];
    FILE* f = fopen(input_file, "r");
    if(f == NULL){
        fprintf(stderr, "err");
        exit(EXIT_FAILURE);
    }
    while((c = fgetc(f)) != EOF){
        if('A' <= c && c <= 'Z'){
            arr[c - 'A']++;
        }else if('a' <= c && c <= 'z'){
            arr[c - 'a']++;
        }
    }
    int ans = arrayMax(arr, 26);
    if(0 <= ans && ans < 26){
        printf("%d", (ans - 4 + 26) % 26);
    }else{
        fprintf(stderr, "err");
        exit(EXIT_FAILURE);
    }
    fclose(f);
}