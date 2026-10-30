#include <stdio.h>
#include <stdlib.h>


struct _retire_info{
    int months;
    double contribution;
    double rate_of_return;
};

typedef struct _retire_info retire_info;

struct _info{
    int months;
    double initial_value;
};

typedef struct _info info;

info answer(int startAge, double initial, retire_info current){
    for(int i = 0; i < current.months; i++){
        printf("Age %3d month %2d you have $%.2f\n", startAge / 12, startAge % 12, initial);
        initial += initial * current.rate_of_return;
        initial += current.contribution;
        startAge++;
    }
    info ans; ans.months = startAge; ans.initial_value = initial;
    return ans;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
    info ans = answer(startAge, initial, working);
    answer(ans.months, ans.initial_value, retired);
}

int main(){
    retire_info working = {489, 1000, 0.045/12};
    retire_info retired = {384, -4000, 0.01/12};
    retirement(327, 21345, working, retired);
    return 0;
}