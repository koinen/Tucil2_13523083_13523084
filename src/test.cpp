#include <fmt/core.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main() {
    const char* filename = "test/example.png";
    int width, height, channels;

    // Load the image
    unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
    if (img == nullptr) {
        fmt::print(stderr, "Failed to load image: {}\n", filename);
        return 1;
    }

    fmt::print("Image loaded successfully!\n");
    fmt::print("Width: {}, Height: {}, Channels: {}\n", width, height, channels);

    // Free the image memory
    stbi_image_free(img);

    return 0;
}