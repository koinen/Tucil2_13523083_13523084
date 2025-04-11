#include <iostream>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./include/Image.hpp"
#include "./include/ErrorMeasure.hpp"
#include "./include/QuadTree.hpp"
#include "./include/GIF.hpp"


int main() {

    cout << "\x1B[2J\x1B[H"; // "clear console" (moves cursor to top left)

    char* ASCII = u8R"(
========================================================================
 _____            _            _                       _ _                 
|_   _|          (_)          (_)                     | | |                
  | |  _ ____   ___ _ __   ___ _  __ _ _   _  __ _  __| | |_ _ __ ___  ___ 
  | | | '_ \ \ / / | '_ \ / __| |/ _` | | | |/ _` |/ _` | __| '__/ _ \/ _ \
  |_| |_| | | \ V /| | | | | (__| | (_| | |_| | (_| | (_| | |_| | |  __/  __/
|_____|_| |_|\_/ |_|_| |_|\___|_|\__, |\__,_|\__,_|\__,_|\__|_|  \___|\___|
                                        | |                                    
                                        |_| 
========================================================================                                   
    )";

    cout << ASCII << endl;
    cout << "Stand ready for my compression.\n" << endl;
    cout << "Press ENTER to continue..." << endl;

    cin.get(); // Wait for user input
    cout << "\x1B[2J\x1B[H"; // "clear console" (moves cursor to top left)

    // INPUTS
    // absolute path of input image
    // error method choice
    // threshold value
    // target percentage compression, if not 0, binary search will be used to find the threshold value
    // min block size
    // absolute path of output image
    // absolute path of output gif
    char* inputImagePath = new char[256];
    char* outputImagePath = new char[256];
    int errorMethodChoice;
    double thresholdValue;
    double targetCompressionRatio;
    int minBlockSize;
    char* outputGIFPath = new char[256];
    double minThreshold = 0.0;
    double maxThreshold = 1.0;
    double (*errorMethod)(const Image&, int, int, int, int) = nullptr;
    cout << "=====================================================================" << endl;
    cout << "                         ViltrumCompresser v4.2                      " << endl;
    cout << "=====================================================================" << endl;
    cout << "You are about to compress an image using the ViltrumCompresser.\n" << endl;
    cout << "Please provide the following information:" << endl;
    cout << "-> Absolute Path to Image: ";
    cin.getline(inputImagePath, 256);
    //check if the file exists
    if (fstream(inputImagePath)) {
    } else {
        cout << "IMAGE NOT FOUND! YOU HAVE TO CHOOSE THE RIGHT PATH, MARK!" << endl;
        return 1;
    }

    // Error method choice
    cout << "-> Error Method Choice (1: Variance, 2: Mean Absolute Deviation, 3: Max Pixel Difference, 4: Entropy Error, 5: SSIM): ";
    cin >> errorMethodChoice;

    if (errorMethodChoice == 1) {
        errorMethod = ErrorMeasure::varianceThreshold;
    } else if (errorMethodChoice == 2) {
        errorMethod = ErrorMeasure::meanAbsoluteDeviationThreshold;
    } else if (errorMethodChoice == 3) {
        errorMethod = ErrorMeasure::maxPixelDifferenceThreshold;
    } else if (errorMethodChoice == 4) {
        errorMethod = ErrorMeasure::entropyErrorThreshold;
    } else if (errorMethodChoice == 5) {
        errorMethod = ErrorMeasure::SSIMThreshold;
    } else {
        cout << "Invalid choice. YOU HAVE TO CHOOSE BETWEEN 1 and 4, MARK!" << endl;
        return 1;
    }


    // Threshold value is set based on the error method choice
    if(errorMethodChoice == 1) {
        cout << "-> Threshold Value (0.0 - 0.25): ";
        cin >> thresholdValue;
        if (thresholdValue < 0.0 || thresholdValue > 0.25) {
            cout << "Invalid threshold. YOU HAVE TO CHOOSE BETWEEN 0.0 and 0.25, MARK!" << endl;
            return 1;
        }
    } else if (errorMethodChoice == 2) {
        cout << "-> Threshold Value (0.0 - 0.5): ";
        cin >> thresholdValue;
        if (thresholdValue < 0.0 || thresholdValue > 0.5) {
            cout << "Invalid threshold. YOU HAVE TO CHOOSE BETWEEN 0.0 and 0.5, MARK!" << endl;
            return 1;
        }
    } else if (errorMethodChoice == 3) {
        cout << "-> Threshold Value (0.0 - 1.0): ";
        cin >> thresholdValue;
        if (thresholdValue < 0.0 || thresholdValue > 1.0) {
            cout << "Invalid threshold. YOU HAVE TO CHOOSE BETWEEN 0.0 and 1.0, MARK!" << endl;
            return 1;
        }
    } else if (errorMethodChoice == 4) {
        cout << "-> Threshold Value (0.0 - 8.0): ";
        cin >> thresholdValue;
        if (thresholdValue < 0.0 || thresholdValue > 8.0) {
            cout << "Invalid threshold. YOU HAVE TO CHOOSE BETWEEN 0.0 and 8.0, MARK!" << endl;
            return 1;
        }
    } else if (errorMethodChoice == 5) {
        cout << "-> Threshold Value (0.0 - 1.0): ";
        cin >> thresholdValue;
        if (thresholdValue < 0.0 || thresholdValue > 1.0) {
            cout << "Invalid threshold. YOU HAVE TO CHOOSE BETWEEN 0.0 and 1.0, MARK!" << endl;
            return 1;
        }
        thresholdValue *= -1; // Invert the threshold value for SSIM
    }

    cout << "-> Target Compression Ratio (0.0 - 1.0): ";
    cin >> targetCompressionRatio;
    if (targetCompressionRatio < 0.0 || targetCompressionRatio > 1.0) {
        cout << "Baka. That is an Invalid compression ratio. YOU HAVE TO CHOOSE BETWEEN 0.0 and 1.0, MARK!" << endl;
        return 1;
    }

    cout << "-> Minimum Block Size (1 <= ): ";
    cin >> minBlockSize;
    if (minBlockSize < 1) {
        cout << "Invalid block size. YOU HAVE TO CHOOSE A BLOCK SIZE GREATER THAN OR EQUAL TO 1, MARK!" << endl;
        return 1;
    }
    cin.ignore(); // Clear the newline character from the input buffer
    cout << "-> Absolute Path to Output Image: ";
    cin.getline(outputImagePath, 256);
    cout << "-> Absolute Path to Output GIF: ";
    cin.getline(outputGIFPath, 256);
    cout << "\x1B[2J\x1B[H"; // "clear console" (moves cursor to top left)
    cout << "=====================================================================" << endl;
    cout << "You have provided the following information:" << endl;
    cout << "-> Absolute Path to Image: " << inputImagePath << endl;
    cout << "-> Error Method Choice: " << errorMethodChoice << endl;
    cout << "-> Threshold Value: " << thresholdValue << endl;
    cout << "-> Target Compression Ratio: " << targetCompressionRatio << endl;
    cout << "-> Minimum Block Size: " << minBlockSize << endl;
    cout << "-> Absolute Path to Output Image: " << outputImagePath << endl;
    cout << "-> Absolute Path to Output GIF: " << outputGIFPath << endl;
    cout << "=====================================================================" << endl;
    cout << "Are you sure?\n" << endl;
    cout << "Press ENTER to continue or CTRL+C to cancel..." << endl;
    cin.get(); // Wait for user input
    cout << "\x1B[2J\x1B[H"; // "clear console" (moves cursor to top left)
    cout << "=====================================================================" << endl;
    cout << "compressing..." << endl;
    cout << "=====================================================================" << endl;
    auto start = chrono::high_resolution_clock::now(); // Start timer

    Image image(inputImagePath); // Load image
    QuadTree quadTree(&image); // Create quadtree

    if(targetCompressionRatio > 0){
        // Binary search for threshold value
        thresholdValue = QuadTree::binarySearchThreshold(inputImagePath, outputImagePath, minBlockSize, image, errorMethod, minThreshold, maxThreshold, targetCompressionRatio);
    }

    // Build quadtree with the given threshold value
    quadTree.buildTree(minBlockSize, thresholdValue, errorMethod);
    Image compressedImage = quadTree.renderImage(quadTree.getMaxDepth()); // Render image from quadtree
    compressedImage.saveImage(outputImagePath); // Save image to file
    cout << "Image saved successfully." << endl;
    auto end1 = chrono::high_resolution_clock::now(); // End timer
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start).count(); // Calculate duration in milliseconds
    Image *frames = new Image[quadTree.getMaxDepth() + 1]; // Create frames for GIF
    for (int i = 0; i <= quadTree.getMaxDepth(); i++) {
        frames[i] = quadTree.renderImage(i); // Render image from quadtree
    }
    GIF::saveGIF(outputGIFPath, frames, quadTree.getMaxDepth() + 1); // Save GIF to file





    auto end2 = chrono::high_resolution_clock::now(); // End timer
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start).count(); // Calculate duration in milliseconds
    cout << "=======================================================" << endl;
    cout << "Image compression completed in " << duration1 << " milliseconds." << endl;
    cout << "GIF creation completed in " << duration2 << " milliseconds." << endl;
    cout << "Previous image size: " << ErrorMeasure::getFileSize(inputImagePath) << " KB" << endl;
    cout << "Compressed image size: " << ErrorMeasure::getFileSize(outputImagePath) << " KB" << endl;
    cout << "Compression ratio: " << (ErrorMeasure::getFileSize(outputImagePath) / ErrorMeasure::getFileSize(inputImagePath)) * 100 << "%" << endl;
    cout << "Depth of quadtree: " << quadTree.getMaxDepth() << endl;
    cout << "Number of nodes in quadtree: " << quadTree.getNodeCount() << endl;
    cout << "Compressed image saved to: " << outputImagePath << endl;
    cout << "GIF saved to: " << outputGIFPath << endl;
    cout << "=======================================================" << endl;







    // OUTPUTS
    // execution time
    // file size of original image
    // file size of compressed image
    // compression ratio
    // depth of quadtree
    // number of nodes in quadtree
    // the compressed image
    // the gif of the quadtree


    // double threshold = QuadTree::binarySearchThreshold(inputImagePath, outputImagePath, 1, image, ErrorMeasure::maxPixelDifferenceThreshold, 0.0, 1.0, 0.5, 10);


    // QuadTree quadTree(&image);
    // quadTree.buildTree(1, 0.1, ErrorMeasure::maxPixelDifferenceThreshold);
    // Image renderedImage = quadTree.renderImage(quadTree.getMaxDepth());
    
    // cout << "Image loaded successfully." << endl;
    // renderedImage.printImageDetails();
    // renderedImage.saveImage("test/output.png");
    
    // cout << "Image saved successfully." << endl;

    // Image *frames = new Image[quadTree.getMaxDepth() + 1];
    // for (int i = 0; i <= quadTree.getMaxDepth(); i++) {
    //     frames[i] = quadTree.renderImage(i);
    // }

    // GIF::saveGIF("test/output.gif", frames, quadTree.getMaxDepth() + 1);
    
    // cout << "Variance Threshold: " << ErrorMeasure::varianceThreshold(image) << endl;
    // cout << "Mean Absolute Deviation Threshold: " << ErrorMeasure::meanAbsoluteDeviationThreshold(image) << endl;
    // cout << "Max Pixel Difference Threshold: " << ErrorMeasure::maxPixelDifferenceThreshold(image) << endl;
    return 0;
}
