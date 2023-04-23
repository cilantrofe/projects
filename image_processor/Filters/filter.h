#pragma once

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "../Image/image.h"
#include "../Read_and_Write/magic.h"

namespace filter {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;

    virtual Image App(const Image& img) const = 0;

protected:
    std::vector<int> AppMatrix(const std::vector<std::vector<int>>& matrix, const Image& img, size_t x, size_t y) const;
};
}  // namespace filter