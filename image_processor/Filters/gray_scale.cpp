#include "gray_scale.h"

Image GrayScale::App(const Image& img) const {
    std::vector<std::vector<Color>> res;
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        std::vector<Color> tmp(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            const Color& pixel = img.GetColor(i, j);
            int gray = static_cast<int>(round(magic::GRAY_SCL_RED * pixel.red + magic::GRAY_SCL_GREEN * pixel.green +
                                              magic::GRAY_SCL_BLUE * pixel.blue));
            tmp[j] = {static_cast<uint8_t>(gray), static_cast<uint8_t>(gray), static_cast<uint8_t>(gray)};
        }
        res.push_back(tmp);
    }
    Image result(res);
    return result;
}