// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_edge1_fill) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 1;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}
TEST(test_edge1_row_col) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 1;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, value);
    const int *ptr = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  delete mat; // delete the Matrix
}
TEST(test_edge1_border) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 1;
  const int height = 1;
  const int value = 42;
  Matrix_init(mat, width, height);
    Matrix_fill_border(mat, value);
    Matrix_fill_border(mat, value);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 42);
  delete mat; // delete the Matrix
}
TEST(test_edge2_border) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 2;
  const int height = 2;
  const int value = 42;
  Matrix_init(mat, width, height);
    Matrix_fill_border(mat, value);
    Matrix *mat1 = new Matrix;
    Matrix_init(mat1, width, height);
    Matrix_fill(mat1, value);
    ASSERT_TRUE(Matrix_equal(mat, mat1));
    delete mat1;
    *Matrix_at(mat, 1, 1) = 43;
    *Matrix_at(mat, 0, 0) = 41;
    ASSERT_EQUAL(Matrix_max(mat), 43);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 2), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 2), 41);
//    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 42);
  delete mat; // delete the Matrix
}
TEST(test_init) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);

    for(int r = 0; r < height; ++r){
        for(int c = 0; c < width; ++c){
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

  delete mat; // delete the Matrix
}
TEST(test_row_col) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    int *ptr = Matrix_at(mat, 1, 1);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 1);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 1);
    
    for(int r = 0; r < height; ++r){
        for(int c = 0; c < width; ++c){
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

  delete mat; // delete the Matrix
}
TEST(test_basic_at) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 0);
    Matrix_print(mat, std::cout);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 0);
    long ptr  = Matrix_at(mat, 4, 2) - Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(ptr, 14);
    ASSERT_EQUAL(*Matrix_at(mat, 4, 2), 0);
    ASSERT_FALSE(*Matrix_at(mat, 3, 1) == 0);
    

  delete mat; // delete the Matrix
}
TEST(test_basic_max) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 0;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 1);
    Matrix_print(mat, std::cout);
    *Matrix_at(mat, 3, 1) = 42;
    ASSERT_EQUAL(Matrix_max(mat), 42);
    

  delete mat; // delete the Matrix
}
TEST(test_edge_max) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 1;
    const int height = 1;
    const int value = -2147483647;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    ASSERT_EQUAL(Matrix_max(mat), -2147483647);

  delete mat; // delete the Matrix
}
TEST(test_basic_col_of_min) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 4;
    const int height = 4;
    const int value = 0;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    *Matrix_at(mat, 1, 1) = -2147483647;
    int minCol = Matrix_column_of_min_value_in_row(mat, 1, 0, width);
    ASSERT_EQUAL(minCol, 1);

  delete mat; // delete the Matrix
}
TEST(test_basic_min_in_row) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 4;
    const int height = 4;
    const int value = 0;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    *Matrix_at(mat, 1, 1) = -2147483647;
    int min = Matrix_min_value_in_row(mat, 1, 0, width);
    ASSERT_EQUAL(min, -2147483647);
    *Matrix_at(mat, 1, 2) = -2147483647;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 3), 1);
    

  delete mat; // delete the Matrix
}
TEST(test_edge_min_max) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 1;
    const int height = 1;
    const int value = -2147483647;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    

    Matrix_fill(mat, value);
    int min = Matrix_min_value_in_row(mat, 0, 0, width);
    ASSERT_EQUAL(min, -2147483647);
    int max = Matrix_max(mat);
    ASSERT_EQUAL(max, -2147483647);
    int colMin = Matrix_column_of_min_value_in_row(mat, 0, 0, width);
    ASSERT_EQUAL(colMin, 0);
    

  delete mat; // delete the Matrix
}
TEST(test_edge1_init) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 1;
    const int height = 1;
    const int value = 0;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 0);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 0);
    Matrix_print(mat, std::cout);

  delete mat; // delete the Matrix
}
TEST(test_edge2_init) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = MAX_MATRIX_WIDTH;
    const int height = MAX_MATRIX_HEIGHT;
    const int value = 0;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 0);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 0);
    ASSERT_EQUAL(*Matrix_at(mat, 100, 100), 0);

  delete mat; // delete the Matrix
}
TEST(test_basic_all) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 5;
    const int height = 5;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 1);
    *Matrix_at(mat, 0, 0) = 41;
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 41);
    Matrix_fill_border(mat, 0);
    const int *ptr = Matrix_at(mat, 3, 3);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 3);
    *Matrix_at(mat, 0, 0) = 41;
    ASSERT_EQUAL(Matrix_max(mat), 41);
    Matrix_fill(mat, 100);
    *Matrix_at(mat, 1, 1) = 41;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 3), 41)
  delete mat; // delete the Matrix
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
