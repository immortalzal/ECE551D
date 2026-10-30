int * arrayMax(int * array, int n) {
    if(n == 0){
        return NULL;
    }
    int ans = -2147483648;
    int index = -1;
    for(int i = 0; i < n; i++){
        if(array[i] > ans){
            ans = array[i];
            index = i;
        }
    }
    return array + index;
}