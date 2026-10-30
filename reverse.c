void reverse(char * str){
    if(str == NULL){
        return;
    }
    int n = strlen(str); 
    int i = 0; char buff;
    while(i < n / 2){
        buff = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = buff;
        i++;
    }
}

int main(){
    reverse("");
}