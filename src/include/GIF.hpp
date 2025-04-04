#ifndef GIF_HPP
#define GIF_HPP

#include <gif_lib.h>
#include "Image.hpp"

class GIF {
    public:
        static GifColorType* createColorPalette(Image img, int colorCount);
        static void saveGIF(const char* fileName, Image* images, int frameCount);
};

#endif