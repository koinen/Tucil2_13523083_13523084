#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <Eigen/Dense>
#include <stb_image.h>
#include <stb_image_write.h>
#include <iostream>
#include <string>

using namespace Eigen;
using namespace std;

class Image {
private:
    int width, height;
    MatrixXd red, green, blue;    

public:
    // MUST USE LOADIMAGE TO INITIALIZE THE IMAGE
    Image();
    Image(const int width, const int height);
    Image(const Image& topLeft, const Image& topRight, const Image& bottomLeft, const Image& bottomRight);
    void loadImage(const char* filename);
    void saveImage(const char* filename) const;

    MatrixXd Red() const;
    MatrixXd Green() const;
    MatrixXd Blue() const;

    double getAvgRedBlock(int x, int y, int width, int height) const;
    double getAvgGreenBlock(int x, int y, int width, int height) const;
    double getAvgBlueBlock(int x, int y, int width, int height) const;
    
    void setColorRed(double avg);
    void setColorGreen(double avg);
    void setColorBlue(double avg);

    void printImageDetails();
};

#endif