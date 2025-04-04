#ifndef ERROR_MEASURE_HPP
#define ERROR_MEASURE_HPP

#include "Image.hpp"


using namespace Eigen;
using namespace std;

class ErrorMeasure {
public:
    static double Variance(const MatrixXd& matrix, int x1, int y1, int x2, int y2);
    static double MeanAbsoluteDeviation(const MatrixXd& matrix, int x1, int y1, int x2, int y2);
    static double MaxPixelDifference(const MatrixXd& matrix, int x1, int y1, int x2, int y2);

    static double varianceThreshold(const Image& image, int x1, int y1, int x2, int y2);
    static double meanAbsoluteDeviationThreshold(const Image& image, int x1, int y1, int x2, int y2);
    static double maxPixelDifferenceThreshold(const Image& image, int x1, int y1, int x2, int y2);
};

#endif
