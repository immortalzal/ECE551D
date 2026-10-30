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

point_t get_location_at(const planet_t * p, double time){
    point_t ans;
    double deg = p -> init_pos + time / (p -> year_len) * 2 * M_PI;
    double radius = p -> orbital_radius;
    ans.x = radius * cos(deg);
    ans.y = radius * sin(deg);
    return ans;
}