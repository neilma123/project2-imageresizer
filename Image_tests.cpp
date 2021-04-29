// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}


// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.
TEST(test_edge_1x1) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel black = {0, 0, 0};

  Image_init(img, 1, 1);
  Image_set_pixel(img, 0, 0, black);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
    Pixel *px1 = new Pixel;
    *px1 = Image_get_pixel(img, 0, 0);
    Pixel *px = new Pixel;
    px->r = 0;
    px->g = 0;
    px->b = 0;
    assert(Pixel_equal(*px1, *px));
    delete px1;
    delete px;
    Pixel *px2 = new Pixel;
    px2->r = 0;
    px2->g = 0;
    px2->b = 1;
    Image_fill(img, *px2);
    Pixel *px3 = new Pixel;
    px3->r = 0;
    px3->g = 0;
    px3->b = 1;
    assert(Pixel_equal(*px2, *px3));
    delete px2;
    delete px3;
    

  delete img; // delete the Image
}
TEST(test_init_fill) {
  Image *img = new Image; // create an Image in dynamic memory
    const int width = 2;
    const int height = 2;

    const Pixel black = {0, 0, 0};

    Image_init(img, width, height);
    Image_fill(img, black);
    // Capture our output
    ostringstream s;
    Image_print(img, s);

    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "0 0 0 0 0 0 \n";
    correct << "0 0 0 0 0 0 \n";
    ASSERT_EQUAL(s.str(), correct.str());

    delete img; // delete the Image
}
TEST(test_basic_all) {
    Image *img = new Image; // create an Image in dynamic memory
    const int width = 2;
    const int height = 2;

    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};

    Image_init(img, width, height);
    ASSERT_EQUAL(Image_width(img), 2);
    ASSERT_EQUAL(Image_height(img), 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);
    Pixel test1 = Image_get_pixel(img, 1, 1);
    ASSERT_EQUAL(test1.r, 255);
    ASSERT_EQUAL(test1.g, 255);
    ASSERT_EQUAL(test1.b, 255);
    // Capture our output
    ostringstream s;
    Image_print(img, s);

    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 \n";
    correct << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct.str());

    delete img; // delete the Image
}
TEST(test_get_and_set) {
    Image *img = new Image; // create an Image in dynamic memory
    Image *copy = new Image;

    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};

    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);
    Pixel test1 = Image_get_pixel(img, 1, 1);
    ASSERT_EQUAL(test1.r, 255);
    ASSERT_EQUAL(test1.g, 255);
    ASSERT_EQUAL(test1.b, 255);
    
    Image_init(copy, 2, 2);
    Image_set_pixel(copy, 0, 0, white);
    Image_set_pixel(copy, 0, 1, white);
    Image_set_pixel(copy, 1, 0, white);
    Image_set_pixel(copy, 1, 1, white);
    for (int i = 0; i < Image_height(img); ++i){
        for (int j = 0; j < Image_width(img); ++j){
            Image_set_pixel(copy, i, j, Image_get_pixel(img, i, j));
        }
    }
    assert(Image_equal(copy, img));
    // Capture our output
    ostringstream s1;
    Image_print(copy, s1);

    // Correct output
    ostringstream correct1;
    correct1 << "P3\n2 2\n255\n";
    correct1 << "255 0 0 0 255 0 \n";
    correct1 << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s1.str(), correct1.str());

    delete img; // delete the Image
    delete copy;
}
TEST(test_init) {
    Image *img = new Image; // create an Image in dynamic memory


    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};

    Image_init(img, 2, 2);
    ASSERT_EQUAL(Image_height(img), 2);
    ASSERT_EQUAL(Image_width(img), 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);
    Pixel test1 = Image_get_pixel(img, 1, 1);
    ASSERT_EQUAL(test1.r, 255);
    ASSERT_EQUAL(test1.g, 255);
    ASSERT_EQUAL(test1.b, 255);
    // Capture our output
    ostringstream s1;
    Image_print(img, s1);

    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 \n";
    correct << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s1.str(), correct.str());
    delete img; // delete the Image
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
