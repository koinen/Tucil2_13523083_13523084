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
    // image.setColorBlue(0.5);
    // image.setColorGreen(0.5);
    // image.setColorRed(0.5);
    // image.saveImage("test/output.png");
    QuadTree quadTree(0, 0, image.Red().cols(), image.Red().rows(), &image, 1, 0, 0.1, ErrorMeasure::maxPixelDifferenceThreshold);
    Image renderedImage = quadTree.renderImage(quadTree.maxDepth);
    // std::cout << image.Red() << std::endl;
    
    cout << "Image loaded successfully." << endl;
    renderedImage.printImageDetails();
    renderedImage.saveImage("test/output.png");
    // quadTree.printNodeInfo(0);
    
    cout << "Image saved successfully." << endl;
    // cout << "Variance Threshold: " << ErrorMeasure::varianceThreshold(image) << endl;
    // cout << "Mean Absolute Deviation Threshold: " << ErrorMeasure::meanAbsoluteDeviationThreshold(image) << endl;
    // cout << "Max Pixel Difference Threshold: " << ErrorMeasure::maxPixelDifferenceThreshold(image) << endl;
    return 0;
}
