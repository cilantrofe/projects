#include "negative.h"

Image Negative::App(const Image& img) const {
    Image result = img;
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            const Color& color = img.GetColor(i, j);
            result.SetColor(i, j,
                            {static_cast<uint8_t>(magic::MAX_COLOR - color.blue),
                             static_cast<uint8_t>(magic::MAX_COLOR - color.green),
                             static_cast<uint8_t>(magic::MAX_COLOR - color.red)});
        }
    }
    return result;
}