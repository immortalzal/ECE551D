#pragma once
#include "circle.hpp"
#include "point.hpp"
#include <cstdio>
#include <cmath>
#include <algorithm>

Circle::Circle(Point c, double r): center(c), radius(r){
}

void Circle::move (double dx, double dy){
    (this -> center).move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle){
    double dist = (this -> center).distanceFrom(otherCircle.center);
    double r_1 = this -> radius;
    double r_2 = otherCircle.radius;
    if(dist >= r_1 + r_2){
        return 0;
    }else if(dist < abs(r_1 - r_2)){
        double temp = std::min(r_1, r_2);
        return temp * temp * M_PI;
    }else{
        double alpha = acos((dist * dist + r_1 * r_1 - r_2 * r_2) / (2 * dist * r_1));
        double beta = acos((dist * dist - r_1 * r_1 + r_2 * r_2) / (2 * dist * r_2));
        double area_1 = 0.5 * r_1 * r_1 * (2 * alpha - sin(2 * alpha));
        double area_2 = 0.5 * r_2 * r_2 * (2 * beta - sin(2 * beta));
        return area_1 + area_2;
    }
}