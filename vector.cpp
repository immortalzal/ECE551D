#include "vector.hpp"
#include <cstdio>
#include <cmath>


class Vector2D{
    private:
    double x;
    double y;

    public:
    void initVector(double init_x, double init_y){
        x = init_x;
        y = init_y;
    }

    double getMagnitude() const{
        return(std::sqrt(x * x + y * y));
    }

    Vector2D operator+(const Vector2D & rhs){
        Vector2D temp;
        temp.x = this -> x + rhs.x;
        temp.y = this -> y + rhs.y;
        return temp;

    }
    Vector2D & operator+=(const Vector2D & rhs){
        this -> x += rhs.x;
        this -> y += rhs.y;
        return *this;
    }

    double dot(const Vector2D & rhs) const{
        return this -> x * rhs.x + this -> y * rhs.y;
    }
    
    void print() const{
        std::printf("<%.2f, %.2f>\n", x, y);
    }
};