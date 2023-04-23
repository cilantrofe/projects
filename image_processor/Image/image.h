#pragma once

#include <cstddef>
#include <vector>

#include "color.h"

class Image {
public:
    Image() = default;
    Image(size_t height, size_t width);
    explicit Image(const std::vector<std::vector<Color>>& data);
    Image(const Image& img);
    ~Image() = default;

    size_t GetHeight() const;
    size_t GetWidth() const;
    const std::vector<std::vector<Color>>& GetImg() const;
    const Color& GetColor(size_t x, size_t y) const;
    void SetColor(size_t x, size_t y, Color color);

private:
    size_t height_ = 0;
    size_t width_ = 0;
    std::vector<std::vector<Color>> img_;
    void CheckSize(size_t x, size_t y) const;
};