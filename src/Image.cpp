#include "../include/Image.hpp"

Image::Image() : width(0), height(0) {}

void Image::loadImage(const char* filename) {
    unsigned char* img = stbi_load(filename, &width, &height, nullptr, 3);
    if (img == nullptr) {
        cerr << "Failed to load image: " << filename << endl;
        return;
    }

    red.resize(height, width);
    green.resize(height, width);
    blue.resize(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            red(i, j) = img[(i * width + j) * 3] / 255.0;
            green(i, j) = img[(i * width + j) * 3 + 1] / 255.0;
            blue(i, j) = img[(i * width + j) * 3 + 2] / 255.0;
        }
    }
    stbi_image_free(img);
}

MatrixXd Image::Red() const {
    return red;
}

MatrixXd Image::Green() const {
    return green;
}

MatrixXd Image::Blue() const {
    return blue;
}
