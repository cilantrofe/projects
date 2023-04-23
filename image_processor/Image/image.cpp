#include "image.h"
#include <stdexcept>
#include <fstream>

Image::Image(size_t height, size_t width) {
    height_ = height;
    width_ = width;
    img_.resize(height, std::vector<Color>(width));
}

Image::Image(const std::vector<std::vector<Color>>& data) {
    img_ = data;
    height_ = data.size();
    if (!data.empty()) {
        width_ = data[0].size();
    }
}

Image::Image(const Image& img) {
    height_ = img.GetHeight();
    width_ = img.GetWidth();
    img_ = img.GetImg();
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

const std::vector<std::vector<Color>>& Image::GetImg() const {
    return img_;
}

const Color& Image::GetColor(size_t x, size_t y) const {
    CheckSize(x, y);
    return img_[x][y];
}

void Image::SetColor(size_t x, size_t y, Color color) {
    CheckSize(x, y);
    img_[x][y] = color;
}

void Image::CheckSize(size_t x, size_t y) const {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Incorrect coordinates");
    }
}