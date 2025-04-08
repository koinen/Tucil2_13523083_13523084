#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "ErrorMeasure.hpp"

using namespace std;

class QuadTree {
    private:
        int x, y; // Coordinates of the top-left corner of the block

        int width, height; // Dimensions of the block

        bool isLeaf; // True if the node is a leaf node, false if it has children

        QuadTree *topLeftTree; // Pointer to the top-left child
        QuadTree *topRightTree; // Pointer to the top-right child
        QuadTree *bottomLeftTree; // Pointer to the bottom-left child
        QuadTree *bottomRightTree; // Pointer to the bottom-right child

        const Image& image; // image object

        double redVal, greenVal, blueVal; // Average color values for the block

        int maxDepth = 0;

    public:

        static double progress; // Progress of the tree building process

        static long long totalNodes; // Total number of leaf nodes in the tree

        QuadTree(const Image& image);

        QuadTree(int x, int y, int width, int height, const Image& image, int currentDepth = 0);

        ~QuadTree();

        void divide(int currentDepth);

        void buildTree(int minBlockSize, double thresholdValue, double (*errorMeasure)(const Image&, int, int, int, int));

        void setAverageColors();

        int getX() const { return x; }
        int getY() const { return y; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        bool isLeafNode() const { return isLeaf; }

        int getMaxDepth() const { return maxDepth; }

        QuadTree* getTopLeftTree() const { return topLeftTree; }
        QuadTree* getTopRightTree() const { return topRightTree; }
        QuadTree* getBottomLeftTree() const { return bottomLeftTree; }
        QuadTree* getBottomRightTree() const { return bottomRightTree; }

        Image renderImage(int depth);

        void printNodeInfo(int depth) const;
};

#endif // QUADTREE_HPP
