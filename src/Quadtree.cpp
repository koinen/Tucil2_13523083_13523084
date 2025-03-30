#include "../include/QuadTree.hpp"

QuadTree::QuadTree(int x, int y, int width, int height, Image *img) : x(x), y(y), width(width), height(height), isLeaf(true), topLeftTree(nullptr), topRightTree(nullptr), bottomLeftTree(nullptr), bottomRightTree(nullptr), image(img) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
}

QuadTree::~QuadTree() {
    delete topLeftTree;
    delete topRightTree;
    delete bottomLeftTree;
    delete bottomRightTree;
}

void QuadTree::divide() {
    if (width <= 1 && height <= 1) {
        return;
    }

    int halfWidth = width / 2;
    int halfHeight = height / 2;

    topLeftTree = new QuadTree(x, y, halfWidth, halfHeight, image);
    topRightTree = new QuadTree(x + halfWidth, y, width - halfWidth, halfHeight, image);
    bottomLeftTree = new QuadTree(x, y + halfHeight, halfWidth, height - halfHeight, image);
    bottomRightTree = new QuadTree(x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight, image);

    isLeaf = false;
}

void QuadTree::setVal(double redVal, double greenVal, double blueVal) {
    if (isLeaf) {
        std::cout << "balls\n";
        image->red.block(x, y, height, width) = MatrixXd::Constant(height, width, redVal);
        image->green.block(x, y, height, width) = MatrixXd::Constant(height, width, greenVal);
        image->blue.block(x, y, height, width) = MatrixXd::Constant(height, width, blueVal);
    }
}


