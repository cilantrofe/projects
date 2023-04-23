#include "filter.h"

std::vector<int> filter::Filter::AppMatrix(const std::vector<std::vector<int>>& matrix, const Image& img, size_t x,
                                           size_t y) const {
    int red = 0;
    int green = 0;
    int blue = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.front().size(); ++j) {
            red += img.GetColor(std::clamp(y - 1 + j, static_cast<size_t>(0), img.GetWidth()),
                                std::clamp(x - 1 + i, static_cast<size_t>(0), img.GetHeight()))
                       .red *
                   matrix[i][j];
            green += img.GetColor(std::clamp(y - 1 + j, static_cast<size_t>(0), img.GetWidth()),
                                  std::clamp(x - 1 + i, static_cast<size_t>(0), img.GetHeight()))
                         .green *
                     matrix[i][j];
            blue += img.GetColor(std::clamp(y - 1 + j, static_cast<size_t>(0), img.GetWidth()),
                                 std::clamp(x - 1 + i, static_cast<size_t>(0), img.GetHeight()))
                        .blue *
                    matrix[i][j];
        }
    }
    return {red, green, blue};
}