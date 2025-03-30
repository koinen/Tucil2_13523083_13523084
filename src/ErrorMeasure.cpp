#include "../include/ErrorMeasure.hpp"

double ErrorMeasure::Variance(const MatrixXd& matrix) {
    double mean = matrix.mean();
    int rows = matrix.rows();
    int cols = matrix.cols();
    double variance = 0.0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            variance += pow(matrix(i, j) - mean, 2);
        }
    }
    return variance / (rows * cols);
}

double ErrorMeasure::varianceThreshold(const Image& image) {
    double redVar = Variance(image.Red());
    double greenVar = Variance(image.Green());
    double blueVar = Variance(image.Blue());

    double avgVar = (redVar + greenVar + blueVar) / 3.0;

    return avgVar;
}