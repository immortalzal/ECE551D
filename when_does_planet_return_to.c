#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct planet_tag {
  char name[MAX_PLANET_NAME_LEN];
  double orbital_radius;  //in km
  double year_len;        //in hours
  double init_pos;        //in radians
};

struct point_tag {
  double x;
  double y;
};
typedef struct point_tag point_t;

typedef struct planet_tag planet_t;


double when_does_planet_return_to(const planet_t * planet, point_t pos, double start_time){
    double planet_deg = fmod((start_time / (planet -> year_len)) * 2 * M_PI + planet -> init_pos, (2 * M_PI));
    double pos_deg = atan(pos.y / pos.x);
    if(pos.x < 0){
        pos_deg += M_PI;
    }else if(pos.y < 0 && pos.x >= 0){
        pos_deg += 2 * M_PI;
    }
    double temp = pos_deg - planet_deg;
    while(temp < 0){
        temp += 2 * M_PI;
    }
    double time_needed = temp / (2 * M_PI) * (planet -> year_len);
    return start_time + time_needed;
}