#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/Image.hpp"
#include "../include/ErrorMeasure.hpp"
#include "../include/QuadTree.hpp"


int main() {
    const char* filename = "test/example.png";
    Image image;
    image.loadImage(filename);
    QuadTree quadtree(0, 0, image.Red().cols(), image.Red().rows(), &image);
    quadtree.divide();
    QuadTree *topLeft = quadtree.getTopLeftTree();
    topLeft->setVal(0, 0, 0);

    std::cout << "Red Matrix:" << std::endl;
    // std::cout << image.Red() << std::endl;
    
    cout << "Image loaded successfully." << endl;
    cout << "Width: " << image.Red().cols() << ", Height: " << image.Red().rows() << endl;
    image.saveImage("test/output.png");
    cout << "Image saved successfully." << endl;
    // cout << "Variance Threshold: " << ErrorMeasure::varianceThreshold(image) << endl;
    // cout << "Mean Absolute Deviation Threshold: " << ErrorMeasure::meanAbsoluteDeviationThreshold(image) << endl;
    // cout << "Max Pixel Difference Threshold: " << ErrorMeasure::maxPixelDifferenceThreshold(image) << endl;

    return 0;
}
