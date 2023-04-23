#include "read.h"

write_and_read::Reader::Reader(const std::string& file) {
    file_ = file;
}

size_t write_and_read::Reader::BytesToNum(unsigned char* chrs) {
    size_t res = *chrs;
    for (size_t i = 0; i < magic::BYTES_TO_NUM_OFFSETS.size(); ++i) {
        res += *(chrs + i + 1) << magic::BYTES_TO_NUM_OFFSETS[i];
    }
    return res;
}

const size_t write_and_read::GetPaddings(size_t width) {
    return (magic::MAX_PADDINGS - (width * (magic::MAX_PADDINGS - 1))) % magic::MAX_PADDINGS;
}

Image write_and_read::Reader::ReadFile() {
    unsigned char bmp_header[magic::BMP_HEADER_SIZE];
    unsigned char dib_header[magic::DIB_HEADER_SIZE];

    std::ifstream image;
    image.open(file_, std::fstream::in | std::fstream::binary);
    if (!image.is_open()) {
        throw std::invalid_argument("Couldn't open the file");  // СЮДА МОЖНО ДОБАВИТЬ ИНФУ О ФАЙЛЕ
    }
    if (errno == EACCES) {
        throw std::invalid_argument("No rights to open the file");  // + инфа о файле
    }

    image.read(reinterpret_cast<char*>(bmp_header), magic::BMP_HEADER_SIZE);

    if (bmp_header[0] != magic::BMP_FORMAT[0] || bmp_header[1] != magic::BMP_FORMAT[1]) {
        throw std::invalid_argument(file_ + " is not bmp\n");
    }

    try {
        image.read(reinterpret_cast<char*>(dib_header), magic::DIB_HEADER_SIZE);

        uint32_t width = BytesToNum(dib_header + magic::WIDTH_OFFSET);
        uint32_t height = BytesToNum(dib_header + magic::HEIGHT_OFFSET);
        Image image_data(height, width);

        std::vector<std::vector<Color>> img(height);
        std::vector<Color> tmp(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[magic::CNT_OF_COLORS];
                image.read(reinterpret_cast<char*>(pix), magic::CNT_OF_COLORS);
                tmp[j].SetColor(static_cast<uint8_t>(pix[0]), static_cast<uint8_t>(pix[1]),
                                static_cast<uint8_t>(pix[2]));
            }
            img[i] = tmp;
            image.ignore(static_cast<std::streamsize>(GetPaddings(width)));
        }
        image_data = Image(img);
        image.close();
        return image_data;

    } catch (std::exception& e) {
        throw "Error in reading: " + static_cast<std::string>(e.what());
    }
}