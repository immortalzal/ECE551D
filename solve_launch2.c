#include "iter_target.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t compute_launch_by_info_extra(const launch_input_t * this_launch, const planet_list_t * planets, double extra_time){
    launch_result_t ans;
    point_t a, b;
    char* source = this_launch -> src;
    char* dest = this_launch -> dest;
    double time = this_launch -> time;
    const planet_t * source_planet = find_planet(planets, source);
    const planet_t *  dest_planet = find_planet(planets, dest);
    a = get_location_at(source_planet, time);
    b = get_location_at(dest_planet, time + extra_time);
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

launch_result_t solve_launch(const launch_input_t * this_launch, const planet_list_t * planets){
    double dist, total_time, how_long; point_t sps_location, plan_location; 
    const planet_t * dest = find_planet(planets, this_launch -> dest);
    launch_result_t ans, temp;
    ans = compute_launch_by_info(this_launch, planets);
    how_long = 0;
    for(int i = 0; i < this_launch -> max_iterations; i++){
        temp = compute_launch_by_info_extra(this_launch, planets, how_long);
        plan_location = get_location_at(dest, this_launch -> time + temp.duration);
        sps_location = get_location_at(dest, this_launch -> time + how_long);
        dist = sqrt((sps_location.x - plan_location.x) * (sps_location.x - plan_location.x) +  (sps_location.y - plan_location.y) * (sps_location.y - plan_location.y));
        total_time = when_does_planet_return_to(dest, sps_location, this_launch -> time + temp.duration) - this_launch -> time;
        if(total_time < ans.duration || i == 0){
            ans.theta = temp.theta;
            ans.duration = temp.duration;
        }
        if(dist < this_launch -> close_enough){
            if(temp.duration < ans.duration){
                ans.duration = temp.duration;
                ans.theta = temp.theta;
            } 
            return ans; 
        }
        how_long = temp.duration; 
    }
    return ans;
}
