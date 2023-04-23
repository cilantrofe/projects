#pragma once

#include "filter.h"

class GrayScale : public filter::Filter {
public:
    Image App(const Image& img) const override;
};