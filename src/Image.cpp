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

void Image::saveImage(const char* filename) const {
    int channels = 3;
    unsigned char* img = new unsigned char[width * height * channels];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            img[(i * width + j) * channels] = static_cast<unsigned char>(red(i, j) * 255);
            img[(i * width + j) * channels + 1] = static_cast<unsigned char>(green(i, j) * 255);
            img[(i * width + j) * channels + 2] = static_cast<unsigned char>(blue(i, j) * 255);
        }
    }

    if (!stbi_write_png(filename, width, height, channels, img, width * channels)) {
        cerr << "Failed to save image: " << filename << endl;
    }

    delete[] img;
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
