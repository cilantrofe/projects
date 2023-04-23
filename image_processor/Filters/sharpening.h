#pragma once

#include "filter.h"

class Sharpening : public filter::Filter {
public:
    Image App(const Image& img) const override;
};