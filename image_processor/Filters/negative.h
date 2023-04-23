#pragma once

#include "filter.h"

class Negative : public filter::Filter {
public:
    Image App(const Image& img) const override;
};