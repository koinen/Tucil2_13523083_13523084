#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "Image.hpp"

using namespace std;

class QuadTree {
    private:
        int x, y;
        int width, height;

        bool isLeaf;

        QuadTree *topLeftTree;
        QuadTree *topRightTree;
        QuadTree *bottomLeftTree;
        QuadTree *bottomRightTree;

        Image *image;

        double redVal, greenVal, blueVal;

        const int minBlockSize; // Minimum block size for leaf nodes

        int maxDepth; // Maximum depth of the tree
        
    public:
        QuadTree(int x, int y, int width, int height, Image *image, int minBlockSize = 1);

        ~QuadTree();

        void divide();

        void setAverageColors();

        int getX() const { return x; }
        int getY() const { return y; }

        int getWidth() const { return width; }
        int getHeight() const { return height; }

        bool isLeafNode() const { return isLeaf; }

        QuadTree* getTopLeftTree() const { return topLeftTree; }
        QuadTree* getTopRightTree() const { return topRightTree; }
        QuadTree* getBottomLeftTree() const { return bottomLeftTree; }
        QuadTree* getBottomRightTree() const { return bottomRightTree; }

        Image renderImage(int depth);

        void printNodeInfo(int depth) const;
};

#endif // QUADTREE_HPP
