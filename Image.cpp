// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<string>
// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);
    img->height = height;
    img->width = width;
    Matrix_init(&img->red_channel, width, height);
    Matrix_init(&img->green_channel, width, height);
    Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
    std::string garbage;
    std::string width;
    std::string height;
    is >> garbage >> width >> height >> garbage;
    int ht = stoi(height);
    int wt = stoi(width);
    img->height = ht;
    img->width = wt;
    Matrix_init(&img->red_channel, wt, ht);
    Matrix_init(&img->green_channel, wt, ht);
    Matrix_init(&img->blue_channel, wt, ht);
    std::string red;
    std::string green;
    std::string blue;
    int ctr = 0;
    int ctrCol = 0;
    while (is >> red >> green >> blue){
        int red_int = stoi(red);
        int green_int = stoi(green);
        int blue_int = stoi(blue);
        if (ctrCol == wt){
            ctr += 1;
            ctrCol = 0;
        }
        *Matrix_at(&img->red_channel, ctr, ctrCol) = red_int;
        *Matrix_at(&img->green_channel, ctr, ctrCol) = green_int;
        *Matrix_at(&img->blue_channel, ctr, ctrCol) = blue_int;
        ctrCol += 1;
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
    os << "P3" << std::endl << Image_width(img) << " ";
    os << Image_height(img) << std::endl << "255" << std::endl;
    int height = Image_height(img);
    int width = Image_width(img);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            os << *Matrix_at(&img->red_channel, i, j) << " ";
            os << *Matrix_at(&img->green_channel, i, j) << " ";
            os << *Matrix_at(&img->blue_channel, i, j) << " ";
            if (j == width - 1){
                os << std::endl;
                break;
            }
        }
    }

}


// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
    return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
    return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
        Pixel pixel;
        pixel.r = *Matrix_at(&img->red_channel, row, column);
        pixel.g = *Matrix_at(&img->green_channel, row, column);
        pixel.b = *Matrix_at(&img->blue_channel, row, column);
    return pixel;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
    *Matrix_at(&img->red_channel, row, column) = color.r;
    *Matrix_at(&img->green_channel, row, column) = color.g;
    *Matrix_at(&img->blue_channel, row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
    for (int i = 0; i < Image_height(img); ++i){
        for (int j = 0; j < Image_width(img); ++j){
            Image_set_pixel(img, i, j, color);
        }
    }
}
