#include <cstdio>
#include "point.hpp"
#include <cmath>

Point::Point(): x(0), y(0){
}

void Point::move(double dx, double dy){
    this -> x += dx;
    this -> y += dy;
}

double Point::distanceFrom(const Point & p){
    return std::sqrt((p.x - this -> x) * (p.x - this -> x) + (p.y - this -> y) * (p.y - this -> y));
}