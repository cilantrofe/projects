#include "filter.h"

class Crop : public filter::Filter {
public:
    Crop(size_t width, size_t height);
    Image App(const Image& img) const override;

private:
    size_t width_;
    size_t height_;
};