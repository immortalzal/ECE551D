//eval 1 step 1
#include "myinput.h"
#include <stdio.h>

int min(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

void parse_planet_info(planet_t * planet, char * line) {
    //STEP 1: Write this
    int colon_num = 0; int str_ind = 0; 
    double radius_sum = 0;
    double year_sum = 0;
    double pos_deg = 0;  int i = 0;
    int column_one_dot = 0;
    int column_two_dot = 0;
    int column_three_dot = 0;
    double buff_one = 0.1;
    double buff_two = 0.1;
    double buff_three = 0.1;
    int least_ind_one = 1000000000;
    int least_ind_two = 1000000000;
    int least_ind_three = 1000000000;
    char temp[100];
    while(line[i] != '\0' && line[i] != '\n'){
        if(line[i] == ':'){
            colon_num++;
            if(colon_num > 3){
                fprintf(stderr, "wrong number of fields");
                exit(EXIT_FAILURE);
            }else if(colon_num == 1){
                temp[str_ind] = '\0';
                if(str_ind > 31){
                    fprintf(stderr, "string too long");
                    exit(EXIT_FAILURE);
                }
                strncpy(planet -> name, temp, str_ind + 1);
            }else if(colon_num == 2){
                planet -> orbital_radius = radius_sum;
            }else{
                planet -> year_len = year_sum;
            }
            i++;
            continue;
        }
        if(colon_num == 0){
            if(str_ind > 31){
                fprintf(stderr, "string name too long");
                exit(EXIT_FAILURE);
            }
            temp[str_ind] = line[i];
            str_ind++;
        }else if(colon_num == 1){
            least_ind_one = min(least_ind_one, i);
            if(line[i] == '.'){
                column_one_dot++;
                if(column_one_dot > 1 || i == least_ind_one){
                    fprintf(stderr, "wrong format for position %d", i);
                    exit(EXIT_FAILURE);
                }
                i++;
                continue;
            }else{
                if(line[i] - '0' < 0 || line[i] - '0' > 9){
                    fprintf(stderr, "wrong format for radius");
                    exit(EXIT_FAILURE);
                }
            }
            if(column_one_dot == 0){
                radius_sum = radius_sum * 10;
                radius_sum += line[i] - '0';
            }else{
                radius_sum += (line[i] - '0') * buff_one;
                buff_one *= 0.1;
            }
        }else if(colon_num == 2){
            least_ind_two = min(least_ind_two, i);
            if(line[i] == '.'){
                column_two_dot++;
                if(column_two_dot > 1 || i == least_ind_two){
                    fprintf(stderr, "wrong format for position %d", i);
                    exit(EXIT_FAILURE);
                }
                i++;
                continue;
            }else{
                if(line[i] - '0' < 0 || line[i] - '0' > 9){
                    fprintf(stderr, "wrong format for year");
                    exit(EXIT_FAILURE);
                }
            }
            if(column_two_dot == 0){
                year_sum = year_sum * 10;
                year_sum += line[i] - '0';
            }else{
                year_sum += (line[i] - '0') * buff_two;
                buff_two *= 0.1;
            }
        }else if(colon_num == 3){
            least_ind_three = min(least_ind_three, i);
            if(line[i] == '.'){
                column_three_dot++;
                if(column_three_dot > 1 || i == least_ind_three){
                    fprintf(stderr, "wrong format for position %d", i);
                    exit(EXIT_FAILURE);
                }
                i++;
                continue;
            }else{
                if(line[i] - '0' < 0 || line[i] - '0' > 9){
                    fprintf(stderr, "wrong format for position %d", i);
                    exit(EXIT_FAILURE);
                }
            }
            if(column_three_dot == 0){
                pos_deg = pos_deg * 10;
                pos_deg += line[i] - '0';
            }else{
                pos_deg += (line[i] - '0') * buff_three;
                buff_three *= 0.1;
            }
        }
        i++;
    }
    planet -> init_pos = pos_deg / 360 * 2 * M_PI;
    if(colon_num != 3){
        fprintf(stderr, "wrong number of fields");
        exit(EXIT_FAILURE);
    }
}