#include "../include/QuadTree.hpp"

QuadTree::QuadTree(Image *img) 
    : x(0), y(0), width(img->getWidth()), height(img->getHeight()), isLeaf(true), topLeftTree(nullptr), 
      topRightTree(nullptr), bottomLeftTree(nullptr), bottomRightTree(nullptr), image(img), maxDepth(0) {}

QuadTree::QuadTree(int x, int y, int width, int height, Image *img, int currentDepth)
    : x(x), y(y), width(width), height(height), isLeaf(true), topLeftTree(nullptr), topRightTree(nullptr), 
      bottomLeftTree(nullptr), bottomRightTree(nullptr), image(img), maxDepth(currentDepth) {}

QuadTree::~QuadTree() {
    delete topLeftTree;
    topLeftTree = nullptr;
    delete topRightTree;
    topRightTree = nullptr;
    delete bottomLeftTree;
    bottomLeftTree = nullptr;
    delete bottomRightTree;
    bottomRightTree = nullptr;
}

void QuadTree::divide(int currentDepth) {
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    isLeaf = false;
    topLeftTree = new QuadTree(x, y, halfWidth, halfHeight, image, currentDepth);
    topRightTree = new QuadTree(x + halfWidth, y, width - halfWidth, halfHeight, image, currentDepth);
    bottomLeftTree = new QuadTree(x, y + halfHeight, halfWidth, height - halfHeight, image, currentDepth);
    bottomRightTree = new QuadTree(x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight, image, currentDepth);
}

void QuadTree::buildTree(int minBlockSize, double thresholdValue, double (*errorMeasure)(const Image&, int, int, int, int)) {
    double error = errorMeasure(*image, x, y, x + width - 1, y + height - 1); 
    if (width <= 1 || height <= 1 || width * height <= minBlockSize || error < thresholdValue) {
        isLeaf = true;
    } else {
        divide(maxDepth + 1);
        topLeftTree->buildTree(minBlockSize, thresholdValue, errorMeasure);
        topRightTree->buildTree(minBlockSize, thresholdValue, errorMeasure);
        bottomLeftTree->buildTree(minBlockSize, thresholdValue, errorMeasure);
        bottomRightTree->buildTree(minBlockSize, thresholdValue, errorMeasure);
        maxDepth = max({topLeftTree->maxDepth, topRightTree->maxDepth, bottomLeftTree->maxDepth, bottomRightTree->maxDepth});
    }
    setAverageColors();
}

void QuadTree::setAverageColors() {
    if (isLeaf) {
        redVal = image->getAvgRedBlock(x, y, width, height);
        greenVal = image->getAvgGreenBlock(x, y, width, height);
        blueVal = image->getAvgBlueBlock(x, y, width, height);
    } else {
        redVal = (topLeftTree->redVal + topRightTree->redVal + bottomLeftTree->redVal + bottomRightTree->redVal) / 4.0;
        greenVal = (topLeftTree->greenVal + topRightTree->greenVal + bottomLeftTree->greenVal + bottomRightTree->greenVal) / 4.0;
        blueVal = (topLeftTree->blueVal + topRightTree->blueVal + bottomLeftTree->blueVal + bottomRightTree->blueVal) / 4.0;
    }
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
        return combinedImage;
    }
}

void QuadTree::printNodeInfo(int depth) const {
    cout << "Node at (" << x << ", " << y << ") with size (" << width << ", " << height << ") - Depth: " << depth << endl;
    cout << "Average Colors: (" << redVal << ", " << greenVal << ", " << blueVal << ")" << endl;
    if (!isLeaf) {
        if (topLeftTree) topLeftTree->printNodeInfo(depth + 1);
        if (topRightTree) topRightTree->printNodeInfo(depth + 1);
        if (bottomLeftTree) bottomLeftTree->printNodeInfo(depth + 1);
        if (bottomRightTree) bottomRightTree->printNodeInfo(depth + 1);
    }
    cout << "----------------------------------------" << endl;
}

int QuadTree::getNodeCount() {
    if (isLeaf) {
        return 1;
    } else {
        return 1 + topLeftTree->getNodeCount() + topRightTree->getNodeCount() + bottomLeftTree->getNodeCount() + bottomRightTree->getNodeCount();
    }
}

double QuadTree::binarySearchThreshold(const char* inputPath, const char* outputPath, int minBlockSize, Image& image, double (*errorMeasure)(const Image&, int, int, int, int), double low, double high, double targetCompressionRatio, int iterations) {
    double thresholdTolerance = 0.01;

    if(iterations <= 0) {
        return (low + high) / 2.0;
    }

    double midThreshold = (low + high) / 2.0;
    QuadTree quadTree(&image);
    quadTree.buildTree(minBlockSize, midThreshold, errorMeasure);
    Image renderedImage = quadTree.renderImage(quadTree.getMaxDepth());
    renderedImage.saveImage(outputPath);
    double originalSize = ErrorMeasure::getFileSize(inputPath);
    double compressedSize = ErrorMeasure::getFileSize(outputPath);

    double currentCompressionRatio = compressedSize/originalSize; 

    // cout << "----------------------------------------" << endl;
    // cout << "Compressed image size: " << compressedSize << endl;
    // cout << "Compression Ratio: " << currentCompressionRatio << endl;
    // cout << "Target Compression Ratio: " << targetCompressionRatio << endl;
    // cout << "Threshold: " << midThreshold << endl;
    // cout << "Iterations left: " << iterations << endl;

    if (abs(currentCompressionRatio - targetCompressionRatio) < thresholdTolerance) {
        return midThreshold;
    } else if (currentCompressionRatio < targetCompressionRatio) {
        return binarySearchThreshold(inputPath, outputPath, minBlockSize, image, errorMeasure, low, midThreshold, targetCompressionRatio, iterations - 1);
    } else {
        return binarySearchThreshold(inputPath, outputPath, minBlockSize, image, errorMeasure, midThreshold, high, targetCompressionRatio, iterations - 1);
    }
}

