#include "write.h"

void write_and_read::Writer::BMPWrite(unsigned char* bmp_header, size_t size_of_img) {
    bmp_header[magic::BMP_FORMAT_OFFSET_FIRST] = magic::BMP_FORMAT[magic::BMP_FORMAT_OFFSET_FIRST];
    bmp_header[magic::BMP_FORMAT_OFFSET_SECOND] = magic::BMP_FORMAT[magic::BMP_FORMAT_OFFSET_SECOND];
    NumToBytes(size_of_img, bmp_header + magic::BMP_SIZE_OFFSET);
    bmp_header[magic::BMP_POSITION_OFFSET] = magic::BMP_HEADER_SIZE + magic::DIB_HEADER_SIZE;
}

void write_and_read::Writer::DIBWrite(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[magic::DIB_SIZE_OFFSET] = magic::DIB_HEADER_SIZE;
    NumToBytes(width, dib_header + magic::WIDTH_OFFSET);
    NumToBytes(height, dib_header + magic::HEIGHT_OFFSET);
    dib_header[magic::BITS_PER_PIX_OFFSET] = magic::CNT_OF_BITS_PER_PIX;
    dib_header[magic::NOT_EMPTY_POSITION] = magic::NOT_EMPTY;
}

write_and_read::Writer::Writer(std::string file) {
    file_ = std::move(file);
}

void write_and_read::Writer::NumToBytes(const size_t numb, unsigned char* chrs) {
    for (size_t i = 0; i < sizeof(numb); ++i) {
        chrs[i] = static_cast<unsigned char>(numb >> i * magic::BYTE_SIZE);
    }
}

void write_and_read::Writer::WriteImage(const Image& image) {
    std::ofstream out_file;
    out_file.open(file_, std::ios::out | std::ios::binary);
    if (!out_file.is_open()) {
        throw std::invalid_argument("Couldn't open the file");
    }

    const size_t size_of_file = magic::BMP_HEADER_SIZE + magic::DIB_HEADER_SIZE +
                                image.GetWidth() * image.GetHeight() * magic::CNT_OF_COLORS +
                                GetPaddings(image.GetWidth()) * image.GetHeight();
    unsigned char bmp_header[magic::BMP_HEADER_SIZE] = {0};  // если зануляет не всё - используйте fill
    BMPWrite(bmp_header, size_of_file);
    unsigned char dib_header[magic::DIB_HEADER_SIZE] = {0};
    DIBWrite(dib_header, image.GetWidth(), image.GetHeight());

    out_file.write(reinterpret_cast<char*>(bmp_header), magic::BMP_HEADER_SIZE);
    out_file.write(reinterpret_cast<char*>(dib_header), magic::DIB_HEADER_SIZE);

    unsigned char empty_bytes[magic::CNT_OF_COLORS] = {0, 0, 0};
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            unsigned char blue = static_cast<unsigned char>(image.GetColor(i, j).blue);
            unsigned char green = static_cast<unsigned char>(image.GetColor(i, j).green);
            unsigned char red = static_cast<unsigned char>(image.GetColor(i, j).red);
            unsigned char pix[] = {blue, green, red};
            out_file.write(reinterpret_cast<char*>(pix), magic::CNT_OF_COLORS);
        }
        out_file.write(reinterpret_cast<char*>(empty_bytes),
                       static_cast<std::streamsize>(GetPaddings(image.GetWidth())));
    }
    out_file.close();
}