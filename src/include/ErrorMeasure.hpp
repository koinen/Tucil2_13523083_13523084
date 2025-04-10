#ifndef ERROR_MEASURE_HPP
#define ERROR_MEASURE_HPP

#include "Image.hpp"
#include <math.h>
#include <fstream>


using namespace Eigen;
using namespace std;


class ErrorMeasure {
public:
    static double Variance(const MatrixXd& matrix, int x1, int y1, int x2, int y2);
    static double Covariance(const MatrixXd& matrix, const MatrixXd& matrix2, int x1, int y1, int x2, int y2); 
    static double MeanAbsoluteDeviation(const MatrixXd& matrix, int x1, int y1, int x2, int y2);
    static double MaxPixelDifference(const MatrixXd& matrix, int x1, int y1, int x2, int y2);
    static double entropyError(const MatrixXd& matrix, int x1, int y1, int x2, int y2);

    static double varianceThreshold(const Image& image, int x1, int y1, int x2, int y2); //0.0-0.25
    static double meanAbsoluteDeviationThreshold(const Image& image, int x1, int y1, int x2, int y2);//0.0-0.5
    static double maxPixelDifferenceThreshold(const Image& image, int x1, int y1, int x2, int y2);//0.0-1.0
    static double entropyErrorThreshold(const Image& image, int x1, int y1, int x2, int y2);//0.0-8.0
    static double SSIMThreshold(const Image& image, int x1, int y1, int x2, int y2);//0.0-1.0

    static double getFileSize(const char* filename);
};

#endif
