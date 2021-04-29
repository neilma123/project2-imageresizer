// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<string>
// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
//    Requires
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);
    mat->height = height;
    mat->width = width;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    os << Matrix_width(mat) << " " << Matrix_height(mat) << std::endl;
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            os << *Matrix_at(mat, i, j) << " ";
            if (j == 0){
                continue;
            }
            else if (j % (width - 1) == 0){
                os << std::endl;
                break;
            }
        }
    }
    os << std::endl;
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
    return mat->width;
  
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
    return mat->height;
  
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    assert(mat && ptr);
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            if (Matrix_at(mat, i, j) == ptr){
                return i;
            }
        }
    }
    return 0;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    assert(mat && ptr);
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            if (Matrix_at(mat, i, j) == ptr){
                return j;
            }
        }
    }
    return 0;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    int width = Matrix_width(mat);
    int height = Matrix_height(mat);
    
    assert((0 <= row && row < height) && (0 <= column && column < width));
    int index = (row * width) + column;
    int *ptr = &mat->data[index];
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    int width = Matrix_width(mat);
    int height = Matrix_height(mat);
    
    assert((0 <= row && row < height) && (0 <= column && column < width));
    int index = (row * width) + column;
    const int *ptr = &mat->data[index];
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            *Matrix_at(mat, i, j) = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            if (j % width == 0 || i % height == 0 || j == width - 1 || i == height - 1){
                *Matrix_at(mat, i, j) = value;
            }
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
//    C++ Minimum integer
    int currMax = -2147483648;
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            if (*Matrix_at(mat, i, j) > currMax){
                currMax = *Matrix_at(mat, i, j);
            }
        }
    }
    return currMax;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    assert(0 <= row && row < height);
    assert(0 <= column_start && column_end <= width);
//    C++ Integer max
    int currMin = 2147483647;
    int currCol = 0;
    
    int i = row;
    for (int j = column_start; j < column_end; ++j){
        if (*Matrix_at(mat, i, j) < currMin){
            currMin = *Matrix_at(mat, i, j);
            currCol = j;
        }
    }
    return currCol;
  
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);
    assert(0 <= row && row < height && 0 <= column_start && column_end <= width);
    int currMin = 2147483647;
    for (int col = column_start; col < column_end; ++col){
            if (*Matrix_at(mat, row, col) < currMin){
                currMin = *Matrix_at(mat, row, col);
            }
        }
    return currMin;
}
