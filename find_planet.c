#include <stdio.h>
#include <stdlib.h>

planet_t * find_planet(const planet_list_t * lst, const char * name){
    size_t n = lst -> num_planets;
    for(size_t i = 0; i < n; i++){
        if(strcmp(lst -> planets[i].name, name) == 0){
            return lst -> planets[i];
        }
    }
    fprintf(stderr, "no match found");
    exit(EXIT_FAILURE);
}


