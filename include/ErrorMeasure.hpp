#ifndef ERROR_MEASURE_HPP
#define ERROR_MEASURE_HPP

#include "Image.hpp"

using namespace Eigen;
using namespace std;

class ErrorMeasure {
private:
    static double Variance(const MatrixXd& matrix);

public:
    static double varianceThreshold(const Image& image);
};

#endif
