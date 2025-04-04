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
        Image();
        Image(const char* filename);
        Image(const int width, const int height);
        Image(const Image& topLeft, const Image& topRight, const Image& bottomLeft, const Image& bottomRight);

        void loadImage(const char* filename);
        void saveImage(const char* filename) const;

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        MatrixXd Red() const { return red; }
        MatrixXd Green() const { return green; }
        MatrixXd Blue() const { return blue; }

        double redAt(int x, int y) const { return red(y, x); }
        double greenAt(int x, int y) const { return green(y, x); }
        double blueAt(int x, int y) const { return blue(y, x); }

        void setColorRed(double avg) { red.setConstant(avg); }
        void setColorGreen(double avg) { green.setConstant(avg); }
        void setColorBlue(double avg) { blue.setConstant(avg); }

        double getAvgRedBlock(int x, int y, int width, int height) const { return red.block(y, x, height, width).mean(); }
        double getAvgGreenBlock(int x, int y, int width, int height) const { return green.block(y, x, height, width).mean(); }
        double getAvgBlueBlock(int x, int y, int width, int height) const { return blue.block(y, x, height, width).mean(); }

        void printImageDetails();
};

#endif