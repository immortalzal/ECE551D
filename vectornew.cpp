#include "vector.hpp"
#include <cstdio>
#include <cmath>


Vector2D::Vector2D(): x(0), y(0){
}

Vector2D::Vector2D(double a, double b): x(a), y(b){
}

double Vector2D::getMagnitude() const{
    return(std::sqrt(x * x + y * y));
}

Vector2D Vector2D::operator+(const Vector2D & rhs){
    Vector2D temp;
    temp.x = this -> x + rhs.x;
    temp.y = this -> y + rhs.y;
    return temp;

}
Vector2D & Vector2D::operator+=(const Vector2D & rhs){
    this -> x += rhs.x;
    this -> y += rhs.y;
    return *this;
}

double Vector2D::dot(const Vector2D & rhs) const{
    return this -> x * rhs.x + this -> y * rhs.y;
}
    
void Vector2D::print() const{
    std::printf("<%.2f, %.2f>", x, y);
}
