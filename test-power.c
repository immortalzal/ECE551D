#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int main(){
    if(power(2, 0) != 1){
        return EXIT_FAILURE;
    }
    if(power(2, 2) != 4){
        return EXIT_FAILURE;
    }
    if(power(2, 3) != 8){
        return EXIT_FAILURE;
    }
    if(power(0, 0) != 1){
        return EXIT_FAILURE;
    }
    if(power(0, 2) != 0){
        return EXIT_FAILURE;
    }
    if(power(3, 1) != 3){
        return EXIT_FAILURE;
    }
    if(power(1, 3) != 1){
        return EXIT_FAILURE;
    }
    if(power(-2147483648, 1) != 2147483648){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}