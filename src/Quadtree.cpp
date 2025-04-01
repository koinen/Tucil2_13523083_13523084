#include "../include/QuadTree.hpp"

QuadTree::QuadTree(int x, int y, int width, int height, Image *img, int minBlockSize) : x(x), y(y), width(width), height(height), isLeaf(true), topLeftTree(nullptr), topRightTree(nullptr), bottomLeftTree(nullptr), bottomRightTree(nullptr), image(img), minBlockSize(minBlockSize) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
    setAverageColors(); // Set average colors for the current block
    // std::cout << redVal << " " << greenVal << " " << blueVal << std::endl;
    if (width * height < minBlockSize || width <= 1 || height <= 1) {
        // If the block is small enough, we consider it a leaf node
        isLeaf = true; // No need to divide further
    } else {
        divide(); // Divide the tree into quadrants
    }
}

QuadTree::~QuadTree() {
    delete topLeftTree;
    delete topRightTree;
    delete bottomLeftTree;
    delete bottomRightTree;
}

void QuadTree::divide() {
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    isLeaf = false;
    topLeftTree = new QuadTree(x, y, halfWidth, halfHeight, image, minBlockSize);
    topRightTree = new QuadTree(x + halfWidth, y, width - halfWidth, halfHeight, image, minBlockSize);
    bottomLeftTree = new QuadTree(x, y + halfHeight, halfWidth, height - halfHeight, image, minBlockSize);
    bottomRightTree = new QuadTree(x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight, image, minBlockSize);
}

void QuadTree::setAverageColors() {
    redVal = image->getAvgRedBlock(x, y, width, height);
    greenVal = image->getAvgGreenBlock(x, y, width, height);
    blueVal = image->getAvgBlueBlock(x, y, width, height);
    // std::cout << "Average Colors: (" << redVal << ", " << greenVal << ", " << blueVal << ")" << std::endl;
}

Image QuadTree::renderImage(int depth) {
    if (isLeaf || depth == 0) {
        Image renderedImage(width, height);
        renderedImage.setColorRed(redVal);
        renderedImage.setColorGreen(greenVal);
        renderedImage.setColorBlue(blueVal);
        return renderedImage;
    } else {
        Image topLeftImage = topLeftTree->renderImage(depth - 1);
        Image topRightImage = topRightTree->renderImage(depth - 1);
        Image bottomLeftImage = bottomLeftTree->renderImage(depth - 1);
        Image bottomRightImage = bottomRightTree->renderImage(depth - 1);
        Image combinedImage(topLeftImage, topRightImage, bottomLeftImage, bottomRightImage);
        return combinedImage; // Combine the images from the four quadrants
    }
}

void QuadTree::printNodeInfo(int depth) const {
    std::cout << "Node at (" << x << ", " << y << ") with size (" << width << ", " << height << ") - Depth: " << depth << std::endl;
    std::cout << "Average Colors: (" << redVal << ", " << greenVal << ", " << blueVal << ")" << std::endl;
    if (!isLeaf) {
        if (topLeftTree) topLeftTree->printNodeInfo(depth + 1);
        if (topRightTree) topRightTree->printNodeInfo(depth + 1);
        if (bottomLeftTree) bottomLeftTree->printNodeInfo(depth + 1);
        if (bottomRightTree) bottomRightTree->printNodeInfo(depth + 1);
    }
    std::cout << "----------------------------------------" << std::endl;
}

