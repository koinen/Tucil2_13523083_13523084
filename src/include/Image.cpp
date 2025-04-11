#include "../include/Image.hpp"

Image::Image() : width(0), height(0) {}

Image::Image(const char* filename) {
    loadImage(filename);
}

Image::Image(const Image& image) : width(image.width), height(image.height), red(image.red), green(image.green), blue(image.blue) {}

Image::Image(const int width, const int height) : width(width), height(height) {
    red.resize(height, width);
    green.resize(height, width);
    blue.resize(height, width);
}

Image::Image(const Image& topLeft, const Image& topRight, const Image& bottomLeft, const Image& bottomRight) {
    width = topLeft.width + topRight.width;
    height = topLeft.height + bottomLeft.height;

    red.resize(height, width);
    green.resize(height, width);
    blue.resize(height, width);

    red.block(0, 0, topLeft.height, topLeft.width) = topLeft.red;
    red.block(0, topLeft.width, topRight.height, topRight.width) = topRight.red;
    red.block(topLeft.height, 0, bottomLeft.height, bottomLeft.width) = bottomLeft.red;
    red.block(topLeft.height, topLeft.width, bottomRight.height, bottomRight.width) = bottomRight.red;

    green.block(0, 0, topLeft.height, topLeft.width) = topLeft.green;
    green.block(0, topLeft.width, topRight.height, topRight.width) = topRight.green;
    green.block(topLeft.height, 0, bottomLeft.height, bottomLeft.width) = bottomLeft.green;
    green.block(topLeft.height, topLeft.width, bottomRight.height, bottomRight.width) = bottomRight.green;

    blue.block(0, 0, topLeft.height, topLeft.width) = topLeft.blue;
    blue.block(0, topLeft.width, topRight.height, topRight.width) = topRight.blue;
    blue.block(topLeft.height, 0, bottomLeft.height, bottomLeft.width) = bottomLeft.blue;
    blue.block(topLeft.height, topLeft.width, bottomRight.height, bottomRight.width) = bottomRight.blue;
}

void Image::loadImage(const char* inputPath) {
    unsigned char* img = stbi_load(inputPath, &width, &height, nullptr, 3);
    if (img == nullptr) {
        cerr << "Failed to load image: " << inputPath << endl;
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

void Image::saveImage(const char* outputPath) const {
    int channels = 3;
    unsigned char* img = new unsigned char[width * height * channels];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            img[(i * width + j) * channels] = static_cast<unsigned char>(red(i, j) * 255);
            img[(i * width + j) * channels + 1] = static_cast<unsigned char>(green(i, j) * 255);
            img[(i * width + j) * channels + 2] = static_cast<unsigned char>(blue(i, j) * 255);
            // cout << "Red: " << red(i, j) << ", Green: " << green(i, j) << ", Blue: " << blue(i, j) << endl;
        }
    }
    string file(outputPath);

    if (file.substr(file.size() - 3) == "png") {
        if (!stbi_write_png(outputPath, width, height, channels, img, width * channels)) {
            cerr << "Failed to save image: " << outputPath << endl;
        }
    }
    else {
        if (!stbi_write_jpg(outputPath, width, height, channels, img, 100)) {
            cerr << "Failed to save image: " << outputPath << endl;
        }
    }

    delete[] img;
}

void Image::printImageDetails() {
    cout << "Image Details:" << endl;
    cout << "Width: " << width << ", Height: " << height << endl;
}