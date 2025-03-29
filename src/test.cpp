#include<fmt/core.h>
#include<CImg.h>

using namespace cimg_library;

int main() {
    // Create an image object
    CImg<unsigned char> image(256, 256, 1, 3, 0); // 256x256, 1 layer, 3 channels (RGB), initialized to 0

    // Draw a red diagonal line
    unsigned char red[] = {255, 0, 0};
    image.draw_line(0, 0, 255, 255, red);

    // Display the image
    CImgDisplay display(image, "Sample Image");

    // Keep the display open until the user closes it
    while (!display.is_closed()) {
        display.wait();
    }

    return 0;
}