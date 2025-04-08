#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/Image.hpp"
#include "../include/ErrorMeasure.hpp"
#include "../include/QuadTree.hpp"
#include "../include/GIF.hpp"


int main() {
    std::cout << "\x1B[2J\x1B[H"; // "clear console" (moves cursor to top left)
    const char filename[] = "test/example.png";
    Image image(filename);

    QuadTree quadTree(&image);
    quadTree.buildTree(1, 0.1, ErrorMeasure::maxPixelDifferenceThreshold);
    Image renderedImage = quadTree.renderImage(quadTree.getMaxDepth());
    
    cout << "Image loaded successfully." << endl;
    renderedImage.printImageDetails();
    renderedImage.saveImage("test/output.png");
    
    cout << "Image saved successfully." << endl;

    Image *frames = new Image[quadTree.getMaxDepth() + 1];
    for (int i = 0; i <= quadTree.getMaxDepth(); i++) {
        frames[i] = quadTree.renderImage(i);
    }

    GIF::saveGIF("test/output.gif", frames, quadTree.getMaxDepth() + 1);
    
    // cout << "Variance Threshold: " << ErrorMeasure::varianceThreshold(image) << endl;
    // cout << "Mean Absolute Deviation Threshold: " << ErrorMeasure::meanAbsoluteDeviationThreshold(image) << endl;
    // cout << "Max Pixel Difference Threshold: " << ErrorMeasure::maxPixelDifferenceThreshold(image) << endl;
    return 0;
}
