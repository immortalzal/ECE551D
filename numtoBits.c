#include <stdio.h>
#include <stdlib.h>

void numToBits(uint32_t * nums, int nNums, int * bits, int nBits){
    if(nBits < nNums * 32){
        printf("Invalid call to numToBits! nBits is %d, nNums is %d\n", nBits, nNums);
        return;
    }
    int ctr = 0;
    for(int i = 0; i < nNums; i++){
        int j = 31; int arr[32] = {0};
        while(nums[i] > 0){
            arr[j] = nums[i] % 2;
            nums[i] /= 2;
            j--;
        }
        for(int k = 0; k < 32; k++){
            bits[ctr] = arr[k];
            ctr++;
        }
    }
}