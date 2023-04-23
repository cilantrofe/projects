#include "gaissian_blur.h"

GaissianBlur::GaissianBlur(double sigma) {
    one_dim_size_ = std::ceil(sigma * magic::GAISSIAN_BLUR);
    one_dim_ = std::vector<double>(one_dim_size_);
    const double g_radius = std::ceil(3 * sigma);
    const double pow_sigma = 2 * sigma * sigma;
    double sum = 0;

    for (size_t i = 0; i < one_dim_size_; ++i) {
        one_dim_[i] =
            std::exp((-(static_cast<double>(i) - g_radius) * (static_cast<double>(i) - g_radius)) / pow_sigma);
        sum += one_dim_[i];
    }

    for (size_t i = 0; i < one_dim_size_; ++i) {
        one_dim_[i] /= sum;
        one_dim_[i] /= (sigma * std::sqrt(2 * M_PI));
    }
}

Image GaissianBlur::App(const Image& img) const {
    std::vector<std::vector<Color>> tmp(img.GetHeight(), std::vector<Color>(img.GetWidth()));
    size_t g_radius = one_dim_size_ / 2;

    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            double r_sum = 0;
            double g_sum = 0;
            double b_sum = 0;

            for (size_t k = 0; k < one_dim_size_; ++k) {
                size_t offset =
                    std::clamp(static_cast<size_t>(j + k - g_radius), static_cast<size_t>(0), img.GetWidth() - 1);
                const Color& p = img.GetColor(offset, i);
                const double& elem = one_dim_[k];

                r_sum += p.red * elem;
                g_sum += p.green * elem;
                b_sum += p.blue * elem;
            }

            tmp[j][i] = {std::clamp(static_cast<uint8_t>((b_sum)*std::numeric_limits<uint8_t>::max()),
                                    static_cast<uint8_t>(0), static_cast<uint8_t>(magic::MAX_COLOR)),
                         std::clamp(static_cast<uint8_t>((g_sum)*magic::MAX_COLOR), static_cast<uint8_t>(0),
                                    static_cast<uint8_t>(magic::MAX_COLOR)),
                         std::clamp(static_cast<uint8_t>((r_sum)*magic::MAX_COLOR), static_cast<uint8_t>(0),
                                    static_cast<uint8_t>(magic::MAX_COLOR))};
        }
    }

    Image image(tmp);

    for (size_t j = 0; j < img.GetWidth(); ++j) {
        for (size_t i = 0; i < img.GetHeight(); ++i) {
            double r_sum = 0;
            double g_sum = 0;
            double b_sum = 0;

            for (size_t k = 0; k < one_dim_size_; ++k) {
                size_t offset = std::clamp(i + k - g_radius, static_cast<size_t>(0), img.GetHeight() - 1);
                const Color& p = image.GetColor(j, offset);
                const double& elem = one_dim_[k];

                r_sum += p.red * elem;
                g_sum += p.green * elem;
                b_sum += p.blue * elem;
            }

            tmp[j][i] = {std::clamp(static_cast<uint8_t>((b_sum)*magic::MAX_COLOR), static_cast<uint8_t>(0),
                                    static_cast<uint8_t>(magic::MAX_COLOR)),
                         std::clamp(static_cast<uint8_t>((g_sum)*magic::MAX_COLOR), static_cast<uint8_t>(0),
                                    static_cast<uint8_t>(magic::MAX_COLOR)),
                         std::clamp(static_cast<uint8_t>((r_sum)*magic::MAX_COLOR), static_cast<uint8_t>(0),
                                    static_cast<uint8_t>(magic::MAX_COLOR))};
        }
    }

    return Image(tmp);
}
