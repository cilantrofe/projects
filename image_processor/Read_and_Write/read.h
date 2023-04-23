#pragma once

#include <cerrno>
#include <fstream>
#include <string>

#include "../Image/image.h"
#include "magic.h"

namespace write_and_read {
class Reader {

public:
    explicit Reader(const std::string& file);

    Image ReadFile();

private:
    std::string file_;
    size_t BytesToNum(unsigned char* chrs);
};

const size_t GetPaddings(size_t width);
}  // namespace write_and_read