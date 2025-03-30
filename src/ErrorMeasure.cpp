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

double ErrorMeasure::MeanAbsoluteDeviation(const MatrixXd& matrix) {
    double mean = matrix.mean();
    int rows = matrix.rows();
    int cols = matrix.cols();
    double mad = 0.0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mad += abs(matrix(i, j) - mean);
        }
    }
    return mad / (rows * cols);
}

double ErrorMeasure::meanAbsoluteDeviationThreshold(const Image& image) {
    double redMAD = MeanAbsoluteDeviation(image.Red());
    double greenMAD = MeanAbsoluteDeviation(image.Green());
    double blueMAD = MeanAbsoluteDeviation(image.Blue());

    double avgMAD = (redMAD + greenMAD + blueMAD) / 3.0;

    return avgMAD;
}

double ErrorMeasure::MaxPixelDifference(const MatrixXd& matrix){
    double max = matrix.maxCoeff();
    double min = matrix.minCoeff();
    return max - min;
}

double ErrorMeasure::maxPixelDifferenceThreshold(const Image& image) {
    double redMaxDiff = MaxPixelDifference(image.Red());
    double greenMaxDiff = MaxPixelDifference(image.Green());
    double blueMaxDiff = MaxPixelDifference(image.Blue());

    double avgMaxDiff = (redMaxDiff + greenMaxDiff + blueMaxDiff) / 3.0;

    return avgMaxDiff;
}