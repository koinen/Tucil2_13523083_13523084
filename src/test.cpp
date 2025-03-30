#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/Image.hpp"
#include "../include/ErrorMeasure.hpp"



int main() {
    const char* filename = "test/example.png";
    Image image;
    image.loadImage(filename);
    cout << "Image loaded successfully." << endl;
    cout << "Width: " << image.Red().cols() << ", Height: " << image.Red().rows() << endl;
    cout << "Variance Threshold: " << ErrorMeasure::varianceThreshold(image) << endl;
    return 0;
}
