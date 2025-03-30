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

    void loadImage(const char* filename);
    
    MatrixXd Red() const;
    MatrixXd Green() const;
    MatrixXd Blue() const;
};

#endif