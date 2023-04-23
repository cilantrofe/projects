#pragma once

#include "filter.h"

class EdgeDetection : public filter::Filter {
public:
    explicit EdgeDetection(int threshold);
    Image App(const Image& img) const override;

private:
    int threshold_;
};