#include "../include/GIF.hpp"

#include <vector>
#include <tuple>

using namespace std;

class Bucket {
public:
    int l, r; // left and right bounds of the bucket
    static vector<tuple<double, double, double>> colors; // color space
    static vector<tuple<double, double, double>> res; // resulting colors
    int depth; // depth of the bucket in the tree
    int maxDepth; // max depth of the tree

    Bucket(int l, int r, int maxDepth, int depth = 0) 
        : maxDepth(maxDepth), l(l), r(r), depth(depth) {
        divide(depth);
    }

    void sortColors(int index) {
        if (index == 0) {
            sort(colors.begin() + static_cast<size_t>(l), 
                 colors.begin() + static_cast<size_t>(r), 
                 [](const tuple<double, double, double>& a, const tuple<double, double, double>& b) {
                     return get<0>(a) < get<0>(b);
                 });
        } else if (index == 1) {
            sort(colors.begin() + static_cast<size_t>(l), 
                 colors.begin() + static_cast<size_t>(r), 
                 [](const tuple<double, double, double>& a, const tuple<double, double, double>& b) {
                     return get<1>(a) < get<1>(b);
                 });
        } else if (index == 2) {
            sort(colors.begin() + static_cast<size_t>(l), 
                 colors.begin() + static_cast<size_t>(r), 
                 [](const tuple<double, double, double>& a, const tuple<double, double, double>& b) {
                     return get<2>(a) < get<2>(b);
                 });
        }
    }

    void divide(int depth) {
        if (depth >= maxDepth) {
            double avgR = 0, avgG = 0, avgB = 0;
            for (int i = l; i <= r; i++) {
                avgR += get<0>((colors)[i]);
                avgG += get<1>((colors)[i]);
                avgB += get<2>((colors)[i]);
            }
            avgR /= (r - l + 1);
            avgG /= (r - l + 1);
            avgB /= (r - l + 1);
            res.emplace_back(avgR, avgG, avgB);
            return;
        }
        int mid = (l + r) / 2;
        int index;
        double minR = 0, minG = 0, minB = 0;
        double maxR = 1, maxG = 1, maxB = 1;
        // find the index with the largest range
        for (int i = l; i <= r; i++) {
            minR = min(minR, get<0>((colors)[i]));
            maxR = max(maxR, get<0>((colors)[i]));
            minG = min(minG, get<1>((colors)[i]));
            maxG = max(maxG, get<1>((colors)[i]));
            minB = min(minB, get<2>((colors)[i]));
            maxB = max(maxB, get<2>((colors)[i]));
        }
        double rangeR = maxR - minR;
        double rangeG = maxG - minG;
        double rangeB = maxB - minB;
        if (rangeR >= rangeG && rangeR >= rangeB) {
            index = 0;
        } else if (rangeG >= rangeR && rangeG >= rangeB) {
            index = 1;
        } else {
            index = 2;
        }
        sortColors(index);
        Bucket left(l, mid, maxDepth, depth + 1);
        Bucket right(mid + 1, r, maxDepth, depth + 1);
    }

    static vector<tuple<double, double, double>> quantize(const Image& img, int colorCount) {
        res.clear();
        res.reserve(colorCount);
        int width = img.getWidth();
        int height = img.getHeight();
        colors.clear();
        colors.reserve(width * height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                Bucket::colors.emplace_back(img.redAt(j, i), img.greenAt(j, i), img.blueAt(j, i));
            }
        }
        Bucket bucket(0, colors.size() - 1, log2(colorCount));
        return res;
    }

    static int findNearestColor(double r, double g, double b, GifColorType *res, int colorCount) {
        int nearestIndex = -1;
        double minDistance = -1;
        for (int i = 0; i < colorCount; i++) {
            double distance = sqrt(pow(r - res[i].Red, 2) + 
                               pow(g - res[i].Green, 2) + 
                               pow(b - res[i].Blue, 2));

            if (nearestIndex == -1 || distance < minDistance) {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }
};

vector<tuple<double, double, double>> Bucket::colors;
vector<tuple<double, double, double>> Bucket::res;

/* ******************************************************************* */
/*  Create a color palette for the GIF, using median cut quantization. */
/* ******************************************************************* */
GifColorType* GIF::createColorPalette(const Image& img, int colorCount) {
    vector<tuple<double, double, double>> palette = Bucket::quantize(img, colorCount);
    GifColorType *gifPalette = new GifColorType[colorCount];
    for (int i = 0; i < colorCount; i++) {
        gifPalette[i].Red   = static_cast<int>(get<0>(palette[i]) * 255);
        gifPalette[i].Green = static_cast<int>(get<1>(palette[i]) * 255);
        gifPalette[i].Blue  = static_cast<int>(get<2>(palette[i]) * 255);
    }

    return gifPalette;
}

void GIF::saveGIF(const char* fileName, Image* images, int frameCount) {
    int colorCount = 256;
    GifColorType* palette = createColorPalette(images[frameCount - 1], colorCount);

    int width = images[0].getWidth();
    int height = images[0].getHeight();
    GifFileType* gifFile = EGifOpenFileName(fileName, false, NULL);
    if (!gifFile) {
        cout << "EGifOpenFileName() failed" << endl;
    }

    gifFile->SWidth = width;
    gifFile->SHeight = height;
    gifFile->SColorResolution = 8;
    gifFile->SBackGroundColor = 0;
    gifFile->SColorMap = GifMakeMapObject(256, palette);

    unsigned char appData[] = "NETSCAPE2.0";
    GifAddExtensionBlock(&gifFile->ExtensionBlockCount,
                        &gifFile->ExtensionBlocks,
                        APPLICATION_EXT_FUNC_CODE,
                        11, appData);

    unsigned char loopData[3] = { 1, 0, 0 };  // Infinite loop
    GifAddExtensionBlock(&gifFile->ExtensionBlockCount,
                        &gifFile->ExtensionBlocks,
                        CONTINUE_EXT_FUNC_CODE,
                        3, loopData);

    for (int i = 0; i < frameCount; i++) {
        uint8_t* frameData = new uint8_t[width * height];
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int r = static_cast<int>(images[i].redAt(x, y) * 255);
                int g = static_cast<int>(images[i].greenAt(x, y) * 255);
                int b = static_cast<int>(images[i].blueAt(x, y) * 255);
                frameData[y * width + x] = Bucket::findNearestColor(r, g, b, palette, colorCount);
            }
        }
        SavedImage frame;
        frame.ImageDesc.Left = 0;
        frame.ImageDesc.Top = 0;
        frame.ImageDesc.Width = width;
        frame.ImageDesc.Height = height;
        frame.ImageDesc.Interlace = false;
        frame.ImageDesc.ColorMap = nullptr; 
        frame.RasterBits = frameData;
        frame.ExtensionBlockCount = 0;
        frame.ExtensionBlocks = nullptr;

        GifMakeSavedImage(gifFile, &frame);

        GraphicsControlBlock gcb;
        gcb.DisposalMode = DISPOSE_BACKGROUND;
        gcb.UserInputFlag = false;
        gcb.DelayTime = 100; 
        gcb.TransparentColor = NO_TRANSPARENT_COLOR;

        EGifGCBToSavedExtension(&gcb, gifFile, gifFile->ImageCount - 1);

        delete[] frameData;
    }

    if (EGifSpew(gifFile) == GIF_ERROR) {
        cout << "EGifSpew() failed - " << gifFile->Error << endl;
        EGifCloseFile(gifFile, NULL);
    }
    
    delete[] palette;
}