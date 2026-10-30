#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<T> ** rows;
 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  ~Matrix();
  Matrix & operator=(const Matrix & rhs);
  int getRows() const;
  int getColumns() const;
  const vector<T> & operator[](int index) const;
  vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;
  template<typename S>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<S> & rhs);

};


template <typename T> 
Matrix<T>::Matrix(): numRows(0), numColumns(0), rows(NULL){
}

template <typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c){
    if(r == 0){
        rows = NULL;
        return;
    }
    this -> rows = new vector<T>*[r];
    for(int i = 0; i < r; i++){
        rows[i] = new vector<T>(c);
    }
}
template <typename T>
Matrix<T>::Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns){
    if(numRows == 0){
        rows = NULL;
        return;
    }
    this -> rows = new vector<T>*[rhs.numRows];
    for(int i = 0; i < rhs.numRows; i++){
        rows[i] = new vector<T>(*rhs.rows[i]);
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    if(rows != NULL){
        for(int i = 0; i < numRows; i++){
            delete this -> rows[i];
        }
        delete[] rows;
    }
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix & rhs) {
    
    if(this != &rhs){
        if(rows != NULL){
            for(int i = 0; i < numRows; i++){
                delete rows[i];
            }
            delete[] rows;
        }
        numColumns = rhs.numColumns;
        numRows = rhs.numRows;
        if(numRows == 0){
            rows = NULL;
            return *this;
        }
        vector<T> ** temp = new vector<T>*[numRows];
        for(int i = 0; i < numRows; i++){
            temp[i] = new vector<T>(*rhs.rows[i]);
        }
        rows = temp;
    }
    return *this;
}
template <typename T>
int Matrix<T>::getRows() const {
    return this -> numRows;
}

template <typename T>
int Matrix<T>::getColumns() const {
    return this -> numColumns;
}
template <typename T>
const vector<T> & Matrix<T>::operator[](int index) const {
    assert(index < numRows &&  index >= 0);
    return *rows[index];
}
template <typename T>
vector<T> & Matrix<T>::operator[](int index){
    assert(index < numRows &&  index >= 0);
    return *rows[index];
}

template <typename T>
bool Matrix<T>::operator==(const Matrix & rhs) const {
    if(rhs.numColumns != numColumns || rhs.numRows != numRows){
        return false;
    }
    for(int i = 0; i < rhs.numRows; i++){
        for(int j = 0; j < rhs.numColumns; j++){
            if((*this -> rows[i])[j] != (*rhs.rows[i])[j]){
                return false;
            }
        }
    }
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix & rhs) const {
    assert((rhs.numColumns == numColumns) && (rhs.numRows == numRows));
    Matrix temp(numRows, numColumns);
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            (*temp.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
        }
    }
    return temp;
}

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
    s << "[ ";
    for(int i = 0; i < rhs.numRows; i++){
        s << '{';
        for(size_t j = 0; j < (*rhs.rows[i]).size(); j++){
            s << (*rhs.rows[i])[j];
            if(j < (*rhs.rows[i]).size() - 1){
                s << ", ";
            }
        }
        s << '}';
        if(i < rhs.numRows - 1){
            s << ",\n";
        }
    }
    s << " ]";
    return s;
}


#endif