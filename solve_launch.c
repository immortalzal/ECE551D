#include <stdio.h>
#include <stdlib.h>

struct launch_input_tag {
  double time;              //the time in hours of when this launch happens
  char * src;               //name of the source planet
  char * dest;              //name of the destination planet
  double speed;             //the speed of this ship (km/hr)
  uint64_t max_iterations;  //(Step 4) how many steps do we try
  double close_enough;      //(Step 4) distance we consider success
};

typedef struct launch_input_tag launch_input_t;

struct launch_result_tag {
  double theta;     //angle to launch from src planet
  double duration;  //how many hours is flight
};

typedef struct launch_result_tag launch_result_t;

struct planet_list_tag {
  planet_t ** planets;
  size_t num_planets;
};
typedef struct planet_list_tag planet_list_t;

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

#include "iter_target.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t solve_launch(const launch_input_t * this_launch, const planet_list_t * planets){
    double dist, total_time, how_long; point_t sps_location, plan_location, src_location;
    double speed = this_launch -> speed; 
    launch_result_t ans = compute_launch_by_info(this_launch, planets);
    printf("in launch_result t first: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration);
    const planet_t * dest = find_planet(planets, this_launch -> dest);
    const planet_t * source = find_planet(planets, this_launch -> src);
    src_location = get_location_at(source, this_launch -> time);
    plan_location = get_location_at(dest, this_launch -> time + ans.duration);
    sps_location = get_location_at(dest, this_launch -> time);
    how_long = this_launch -> time + ans.duration;
    ans.duration = when_does_planet_return_to(dest, sps_location, how_long) - this_launch -> time;
    printf("in when_does_planet_return_to first: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration);
    dist = sqrt((sps_location.x - plan_location.x) * (sps_location.x - plan_location.x) +  (sps_location.y - plan_location.y) * (sps_location.y - plan_location.y));
    total_time = ans.duration;
    printf("max iterations: %ld\n", this_launch -> max_iterations);
     if(dist < (this_launch -> close_enough)){
        ans.duration = how_long - this_launch -> time;
	printf("in start + dist loop: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration);
        return ans;
    }
    printf("in start loop: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration); 
    for(int i = 1; i < this_launch -> max_iterations; i++){
        sps_location = get_location_at(dest, how_long);
        how_long = this_launch -> time + sqrt((sps_location.x - src_location.x) * (sps_location.x - src_location.x)+ (sps_location.y - src_location.y) * (sps_location.y - src_location.y)) / speed;
        plan_location = get_location_at(dest, how_long);
        total_time = when_does_planet_return_to(dest, sps_location, how_long) - this_launch -> time;
        if(total_time < ans.duration){
            double angle = atan((sps_location.y - src_location.y) / (sps_location.x - src_location.x));
            if(sps_location.x - src_location.x < 0){
              angle += M_PI;
            }else if(sps_location.y - src_location.y < 0 && sps_location.x - src_location.x >= 0){
                angle += 2 * M_PI;
            }
            ans.theta = angle;
            ans.duration = total_time;
	    printf("in total_time loop %d: ans.theta = %lf, ans.duration = %lf\n", i, ans.theta, ans.duration); 
        }
        dist = sqrt((sps_location.x - plan_location.x) * (sps_location.x - plan_location.x) +  (sps_location.y - plan_location.y) * (sps_location.y - plan_location.y));
        if(dist < (this_launch -> close_enough)){
            if(how_long - this_launch -> time <= ans.duration){
              double angle = atan((sps_location.y - src_location.y) / (sps_location.x - src_location.x));
              if(sps_location.x - src_location.x < 0){
                  angle += M_PI;
              }else if(sps_location.y - src_location.y < 0 && sps_location.x - src_location.x >= 0){
                  angle += 2 * M_PI;
              }
              ans.theta = angle;
              ans.duration = how_long - this_launch -> time;
              printf("in how_long + dist loop: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration);
            }
	    printf("in dist loop: ans.theta = %lf, ans.duration = %lf\n", ans.theta, ans.duration);
            return ans;
        }  
    }
    return ans;
}
