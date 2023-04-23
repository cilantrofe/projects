#pragma once

#include "filter.h"

class GaissianBlur : public filter::Filter {
public:
    explicit GaissianBlur(double sigma);
    Image App(const Image& img) const override;

private:
    std::vector<double> one_dim_;
    size_t one_dim_size_;
};