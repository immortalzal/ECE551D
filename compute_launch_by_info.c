#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct planet_tag planet_t;

struct planet_list_tag {
  planet_t ** planets;
  size_t num_planets;
};
typedef struct planet_list_tag planet_list_t;
struct launch_input_tag {
  double time;              //the time in hours of when this launch happens
  char * src;               //name of the source planet
  char * dest;              //name of the destination planet
  double speed;             //the speed of this ship (km/hr)
  uint64_t max_iterations;  //(Step 4) how many steps do we try
  double close_enough;      //(Step 4) distance we consider success
};
typedef struct launch_input_tag launch_input_t;

struct launch_list_tag {
  launch_input_t ** launches;
  size_t num_launches;
};

struct launch_result_tag {
  double theta;     //angle to launch from src planet
  double duration;  //how many hours is flight
};

typedef struct launch_result_tag launch_result_t;


launch_result_t compute_launch_by_info(const launch_input_t * this_launch, const planet_list_t * planets){
    launch_result_t ans;
    point_t a, b;
    char* source = this_launch -> src;
    char* dest = this_launch -> dest;
    double time = this_launch -> time;
    const planet_t * source_planet = find_planet(planets, source);
    const planet_t *  dest_planet = find_planet(planets, dest);
    a = get_location_at(source_planet, time);
    b = get_location_at(dest_planet, time);
    double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    ans.duration = dist / (this_launch -> speed);
    double angle = atan((b.y - a.y) / (b.x - a.x));
    if(b.x - a.x < 0){
        angle += M_PI;
    }else if(b.y - a.y < 0 && b.x - a.x >= 0){
        angle += 2 * M_PI;
    }
    ans.theta = angle;
    return ans;
}