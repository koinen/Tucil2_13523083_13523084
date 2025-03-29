using namespace std;

class QuadTree {
    private:
        int x, y;
        int width, height;

        bool isLeaf;
        int val;

        QuadTree *topLeftTree;
        QuadTree *topRightTree;
        QuadTree *bottomLeftTree;
        QuadTree *bottomRightTree;
        
    public:
        QuadTree(int x, int y, int width, int height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->isLeaf = true;
            this->val = 0;
            this->topLeftTree = nullptr;
            this->topRightTree = nullptr;
            this->bottomLeftTree = nullptr;
            this->bottomRightTree = nullptr;
        }

        void divide() {
            int width1 = width / 2;
            int height1 = height / 2;
            int width2 = width - width1;
            int height2 = height - height1;

            topLeftTree = new QuadTree(x, y, width1, height1);
            topRightTree = new QuadTree(x + width1, y, width2, height1);
            bottomLeftTree = new QuadTree(x, y + height1, width1, height2);
            bottomRightTree = new QuadTree(x + width1, y + height1, width2, height2);
            isLeaf = false;
        }

        void setVal(int val) {
            this->val = val;
        }
};