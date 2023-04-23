#include "edge_detection.h"
#include "gray_scale.h"

Image EdgeDetection::App(const Image& img) const {
    Image gray_img = GrayScale().App(img);
    std::vector<std::vector<int>> matrix = magic::MATRIX_FOR_EDGE;
    std::vector<std::vector<Color>> res;
    for (size_t i = 0; i < gray_img.GetHeight(); ++i) {
        std::vector<Color> tmp(gray_img.GetWidth());
        for (size_t j = 0; j < gray_img.GetWidth(); ++j) {
            std::vector<int> colors_of_pix = AppMatrix(matrix, gray_img, i, j);
            if (colors_of_pix.front() > threshold_) {
                tmp[j] = {magic::MAX_COLOR, magic::MAX_COLOR, magic::MAX_COLOR};
            } else {
                tmp[j] = {magic::MIN_COLOR, magic::MIN_COLOR, magic::MIN_COLOR};
            }
        }
        res.push_back(tmp);
    }
    Image result(res);
    return result;
}

EdgeDetection::EdgeDetection(int threshold) {
    threshold_ = threshold;
}
