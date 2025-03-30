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
    

public:
    MatrixXd red, green, blue;
    // MUST USE LOADIMAGE TO INITIALIZE THE IMAGE
    Image();
    void loadImage(const char* filename);
    
    void saveImage(const char* filename) const;

    MatrixXd Red() const;
    MatrixXd Green() const;
    MatrixXd Blue() const;
};

#endif