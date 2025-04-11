#include "../include/ErrorMeasure.hpp"

// FOR SSIM
double ErrorMeasure::Covariance(const MatrixXd& matrix, const MatrixXd& matrix2, int x1, int y1, int x2, int y2) {
    int rows = y2 - y1 + 1;
    int cols = x2 - x1 + 1;

    auto block1 = matrix.block(y1, x1, rows, cols);
    auto block2 = matrix2.block(y1, x1, rows, cols);

    double mean1 = block1.mean();
    double mean2 = block2.mean();

    double covariance = ((block1.array() - mean1) * (block2.array() - mean2)).sum();

    return covariance / (rows * cols); // or use (rows * cols - 1) for sample
}

// CHECK IF BLOCK FUNC WORK
double ErrorMeasure::Variance(const MatrixXd& matrix, int x1, int y1, int x2, int y2) {
    double mean = matrix.block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    int rows = y2 - y1 + 1;
    int cols = x2 - x1 + 1;
    double variance = 0.0;

    for (int i = y1; i < y2 + 1; ++i) {
        for (int j = x1; j < x2 + 1; ++j) {
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
    int rows = y2 - y1+1;
    int cols = x2 - x1+1;
    double mad = 0.0;

    for (int i = y1; i < y2+1; ++i) {
        for (int j = x1; j < x2+1; ++j) {
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

double ErrorMeasure::entropyError(const MatrixXd& matrix, int x1, int y1, int x2, int y2) {
    double entropy = 0.0;
    double total = 0.0;
    double histogram[256] = {0};

    for (int i = y1; i < y2 + 1; ++i) {
        for (int j = x1; j < x2 + 1; ++j) {
            histogram[(int)(matrix(i, j) * 255)]++;
            total++;
        }
    }

    for (int i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            double p = histogram[i] / total;
            entropy -= p * log2(p);
        }
    }

    return entropy;
}

double ErrorMeasure::entropyErrorThreshold(const Image& image, int x1, int y1, int x2, int y2) {
    double redEntropy = entropyError(image.Red(), x1, y1, x2, y2);
    double greenEntropy = entropyError(image.Green(), x1, y1, x2, y2);
    double blueEntropy = entropyError(image.Blue(), x1, y1, x2, y2);

    double avgEntropy = (redEntropy + greenEntropy + blueEntropy) / 3.0;

    return avgEntropy;
}

double ErrorMeasure::SSIMThreshold(const Image& image1, int x1, int y1, int x2, int y2) {
    // original.loadImage("test/example.png");
    // C1 from 8-bit, normalized (0-1)

    Image image2(image1);
    double blue = image2.getAvgBlueBlock(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    double green = image2.getAvgGreenBlock(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    double red = image2.getAvgRedBlock(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    image2.setColorRed(red);
    image2.setColorGreen(green);
    image2.setColorBlue(blue);

    double C1 = pow(0.01, 2);

    // C2 from 8-bit, normalized (0-1)
    double C2 = pow(0.03, 2);
    
    // FOR CURRENT IMAGE
    double redMean = image1.Red().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    double greenMean = image1.Green().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    double blueMean = image1.Blue().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();

    double redVar = Variance(image1.Red(), x1, y1, x2, y2);
    double greenVar = Variance(image1.Green(), x1, y1, x2, y2);
    double blueVar = Variance(image1.Blue(), x1, y1, x2, y2);

    // FOR ORIGINAL IMAGE
    double originalRedMean = image2.Red().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    double originalGreenMean = image2.Green().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();
    double originalBlueMean = image2.Blue().block(y1, x1, y2 - y1 + 1, x2 - x1 + 1).mean();

    double originalRedVar = Variance(image2.Red(), x1, y1, x2, y2);
    double originalGreenVar = Variance(image2.Green(), x1, y1, x2, y2);
    double originalBlueVar = Variance(image2.Blue(), x1, y1, x2, y2);

    // SSIM
    double redCov = Covariance(image1.Red(), image2.Red(), x1, y1, x2, y2);
    double greenCov = Covariance(image1.Green(), image2.Green(), x1, y1, x2, y2);
    double blueCov = Covariance(image1.Blue(), image2.Blue(), x1, y1, x2, y2);

    double redSSIM = (2 * redMean * originalRedMean + C1) * (2 * redCov + C2) / ((pow(redMean, 2) + pow(originalRedMean, 2) + C1) * (redVar + originalRedVar + C2));
    double greenSSIM = (2 * greenMean * originalGreenMean + C1) * (2 * greenCov + C2) / ((pow(greenMean, 2) + pow(originalGreenMean, 2) + C1) * (greenVar + originalGreenVar + C2));
    double blueSSIM = (2 * blueMean * originalBlueMean + C1) * (2 * blueCov + C2) / ((pow(blueMean, 2) + pow(originalBlueMean, 2) + C1) * (blueVar + originalBlueVar + C2));

    double avgSSIM = (redSSIM + greenSSIM + blueSSIM) / 3.0;

    return -avgSSIM;
}

double ErrorMeasure::getFileSize(const char* filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename, "rb");
    if (!p_file) {
        cerr << "Error opening file" << endl;
        return -1;
    }
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return double(size) / 1024.0;
}