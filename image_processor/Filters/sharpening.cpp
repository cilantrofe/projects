#include "sharpening.h"

Image Sharpening::App(const Image& img) const {
    Image result = img;

    for (size_t y = 1; y < img.GetHeight() - 1; ++y) {
        for (size_t x = 1; x < img.GetWidth() - 1; ++x) {
            std::vector<std::vector<int>> matrix = magic::MATRIX_FOR_SHARP;
            std::vector<int> new_color = AppMatrix(matrix, img, y, x);
            int r = std::max(0, std::min(magic::MAX_COLOR, new_color[0]));
            int g = std::max(0, std::min(magic::MAX_COLOR, new_color[1]));
            int b = std::max(0, std::min(magic::MAX_COLOR, new_color[2]));
            result.SetColor(x, y, {static_cast<uint8_t>(b), static_cast<uint8_t>(g), static_cast<uint8_t>(r)});
        }
    }

    return result;
}