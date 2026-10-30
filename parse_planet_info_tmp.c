#include "myinput.h"
#include <stdio.h>

void parse_planet_info(planet_t * planet, char * line) {
    //STEP 1: Write this
    int colon_num = 0; int str_ind = 0; 
    double radius_sum = 0;
    double year_sum = 0;
    double pos_deg = 0; int i = 0;
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
                strncpy(planet -> name, temp, 32);
            }else if(colon_num == 2){
                planet -> orbital_radius = radius_sum;
            }else{
                planet -> year_len = year_sum;
            }
        }else if(colon_num == 0){
            if(str_ind > 31){
                fprintf(stderr, "string name too long");
                exit(EXIT_FAILURE);
            }
            temp[str_ind] = line[i];
            str_ind++;
        }else if(colon_num == 1){
            if(line[i] - '0' < 0 || line[i] - '0' > 9){
                fprintf(stderr, "wrong format for radius");
                exit(EXIT_FAILURE);
            }
            radius_sum = radius_sum * 10;
            radius_sum += line[i] - '0';
        }else if(colon_num == 2){
            if(line[i] - '0' < 0 || line[i] - '0' > 9){
                fprintf(stderr, "wrong format for year");
                exit(EXIT_FAILURE);
            }
            year_sum = year_sum * 10;
            year_sum += line[i] - '0';
        }else if(colon_num == 3){
            if(line[i] - '0' < 0 || line[i] - '0' > 9){
                fprintf(stderr, "wrong format for position %d %c", i, line[i]);
                exit(EXIT_FAILURE);
            }
            pos_deg = pos_deg * 10;
            pos_deg += line[i] - '0';
        }
	i++;
    }
    planet -> init_pos = pos_deg / 360 * 2 * M_PI;
    if(colon_num != 3){
        fprintf(stderr, "wrong number of fields");
        exit(EXIT_FAILURE);
    }
}
