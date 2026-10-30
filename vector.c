#include <stdio.h>

struct vector_tag{
    double x;
    double y;
    double z;
};

typedef struct vector_tag vector_t;

double dot_product(vector_t v1, vector_t v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vector_t cross_product(vector_t v1, vector_t v2){
    vector_t v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}