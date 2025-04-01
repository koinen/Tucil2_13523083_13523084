#include "../include/ErrorMeasure.hpp"

// CHECK IF BLOCK FUNC WORK
double ErrorMeasure::Variance(const MatrixXd& matrix, int x1, int y1, int x2, int y2) {
    double mean = matrix.block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    int rows = y2 - y1;
    int cols = x2 - x1;
    double variance = 0.0;

    for (int i = y1; i < y2; ++i) {
        for (int j = x1; j < x2; ++j) {
            variance += (matrix(i, j) - mean) * (matrix(i, j) - mean);
        }
    }
    return variance / (rows * cols);
}

double ErrorMeasure::varianceThreshold(const Image& image, int x1, int y1, int x2, int y2) {
    double redVar = Variance(image.Red(), x1, y1, x2, y2);
    double greenVar = Variance(image.Green(), x1, y1, x2, y2);
    double blueVar = Variance(image.Blue(), x1, y1, x2, y2);

    double avgVar = (redVar + greenVar + blueVar) / 3.0;

    return avgVar;
}

double ErrorMeasure::MeanAbsoluteDeviation(const MatrixXd& matrix, int x1, int y1, int x2, int y2) {
    double mean = matrix.block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    int rows = y2 - y1;
    int cols = x2 - x1;
    double mad = 0.0;

    for (int i = y1; i < y2; ++i) {
        for (int j = x1; j < x2; ++j) {
            mad += abs(matrix(i, j) - mean);
        }
    }
    return mad / (rows * cols);
}

double ErrorMeasure::meanAbsoluteDeviationThreshold(const Image& image, int x1, int y1, int x2, int y2) {
    double redMAD = MeanAbsoluteDeviation(image.Red(), x1, y1, x2, y2);
    double greenMAD = MeanAbsoluteDeviation(image.Green(), x1, y1, x2, y2);
    double blueMAD = MeanAbsoluteDeviation(image.Blue(), x1, y1, x2, y2);

    double avgMAD = (redMAD + greenMAD + blueMAD) / 3.0;

    return avgMAD;
}

double ErrorMeasure::MaxPixelDifference(const MatrixXd& matrix, int x1, int y1, int x2, int y2) {
    MatrixXd block = matrix.block(y1, x1, y2 - y1 + 1, x2 - x1 + 1);
    double min = block.minCoeff();
    double max = block.maxCoeff();

    return max - min;
}

double ErrorMeasure::maxPixelDifferenceThreshold(const Image& image, int x1, int y1, int x2, int y2) {
    double redMaxDiff = MaxPixelDifference(image.Red(), x1, y1, x2, y2);
    double greenMaxDiff = MaxPixelDifference(image.Green(), x1, y1, x2, y2);
    double blueMaxDiff = MaxPixelDifference(image.Blue(), x1, y1, x2, y2);

    double avgMaxDiff = (redMaxDiff + greenMaxDiff + blueMaxDiff) / 3.0;

    return avgMaxDiff;
}