#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray(): data(NULL), numElements(0){}

IntArray::IntArray(int n): numElements(n){
    this -> data = new int[n];
}

IntArray::IntArray(const IntArray & rhs): data(new int[rhs.numElements]), numElements(rhs.numElements) {
    for(int i = 0; i < rhs.numElements; i++){
        data[i] = rhs.data[i];
    }
}
IntArray::~IntArray() {
    delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    if(this != &rhs){
        int* temp = new int[rhs.numElements];
        for(int i = 0; i < rhs.numElements; i++){
            temp[i] = rhs.data[i];
        }
        delete[] data;
        numElements = rhs.numElements;
        data = temp;
    }
    return *this;
}
const int & IntArray::operator[](int index) const {
    assert(index < this -> numElements && index >= 0);
    return data[index];
}
int & IntArray::operator[](int index) {
    assert(index < this -> numElements && index >= 0);
    return data[index];
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    int n_1 = this -> numElements;
    int n_2 = rhs.numElements;
    if(n_1 != n_2){
        return false;
    }
    for(int i = 0; i < n_1; i++){
        if(this -> data[i] != rhs.data[i]){
            return false;
        }
    }
    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    int n_1 = this -> numElements;
    int n_2 = rhs.numElements;
    if(n_1 != n_2){
        return true;
    }
    for(int i = 0; i < n_1; i++){
        if(this -> data[i] != rhs.data[i]){
            return true;
        }
    }
    return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    if(rhs.numElements == 0){
        s << "{}";
        return s;
    }
    s << '{';
    for(int i = 0; i < rhs.numElements - 1; i++){
        s << rhs.data[i] << ", ";
    }
    s << rhs.data[rhs.numElements - 1] << '}';
    return s;
}
