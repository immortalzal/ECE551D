#include "IntMatrix.h"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL){
}
IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c){
    if(r == 0){
        rows = NULL;
        return;
    }
    this -> rows = new IntArray*[r];
    for(int i = 0; i < r; i++){
        rows[i] = new IntArray(c);
    }
}
IntMatrix::IntMatrix(const IntMatrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns){
    if(numRows == 0){
        rows = NULL;
        return;
    }
    this -> rows = new IntArray*[rhs.numRows];
    for(int i = 0; i < rhs.numRows; i++){
        rows[i] = new IntArray(*rhs.rows[i]);
    }
}

IntMatrix::~IntMatrix() {
    if(rows != NULL){
        for(int i = 0; i < numRows; i++){
            delete this -> rows[i];
        }
        delete[] rows;
    }
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
    
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
        IntArray ** temp = new IntArray*[numRows];
        for(int i = 0; i < numRows; i++){
            temp[i] = new IntArray(*rhs.rows[i]);
        }
        rows = temp;
    }
    return *this;
}
int IntMatrix::getRows() const {
    return this -> numRows;
}
int IntMatrix::getColumns() const {
    return this -> numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
    assert(index < numRows &&  index >= 0);
    return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
    assert(index < numRows &&  index >= 0);
    return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
    assert((rhs.numColumns == numColumns) && (rhs.numRows == numRows));
    IntMatrix temp(numRows, numColumns);
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            (*temp.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
        }
    }
    return temp;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
    s << "[ ";
    for(int i = 0; i < rhs.numRows; i++){
        s << *rhs.rows[i];
        if(i < rhs.numRows - 1){
            s << ",\n";
        }
    }
    s << " ]";
    return s;
}
