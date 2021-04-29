// Project UID af1f95f547e44c8ea88730dfb185559d
#include "processing.h"
#include <cassert>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<string>
using namespace std;
int main(int argc, char *argv[]){
    if(argc != 4 && argc != 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    int newWidth = 0;
    int newHeight = 0;
    string filename = argv[1];
    ifstream is;
    is.open(filename);
    if (!is.is_open()){
        cout << "Error opening file: " << filename << endl;
        return 1;
    }
    Image *img = new Image;
    Image_init(img, is);
    
    if (argc == 5){
        string wt = argv[3];
        string ht = argv[4];
        newWidth = stoi(wt);
        newHeight = stoi(ht);
    }
    else if (argc == 4){
        string wt = argv[3];
        newWidth = stoi(wt);
        newHeight = Image_height(img);
    }
    if (!(newWidth > 0 && newWidth <= Image_width(img))
        || !(newHeight > 0 && newHeight <= Image_height(img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    seam_carve(img, newWidth, newHeight);
    string output = argv[2];
    ofstream fout(output);
    Image_print(img, fout);
    delete img;
    return 0;
}
