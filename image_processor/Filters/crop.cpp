#include "crop.h"

Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}

Image Crop::App(const Image& img) const {
    size_t img_width = img.GetWidth();
    size_t img_height = img.GetHeight();
    size_t new_width = std::min(img_width, width_);
    size_t new_height = std::min(img_height, height_);
    Image cropped_img(new_width, new_height);
    for (size_t y = 0; y < new_height; ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            cropped_img.SetColor(x, y, img.GetColor(x, y));
        }
    }
    return cropped_img;
}