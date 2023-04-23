#pragma once

#include <vector>

namespace magic {
const int BMP_HEADER_SIZE = 14;
const int DIB_HEADER_SIZE = 40;
const int WIDTH_OFFSET = 4;
const int HEIGHT_OFFSET = 8;
const int MAX_PADDINGS = 4;
const int CNT_OF_COLORS = 3;
const int BMP_FORMAT_OFFSET_FIRST = 0;
const int BMP_FORMAT_OFFSET_SECOND = 1;
const int BMP_SIZE_OFFSET = 2;
const int BMP_POSITION_OFFSET = 10;
const int DIB_SIZE_OFFSET = 0;
const int CNT_OF_BITS_PER_PIX = 24;
const int BITS_PER_PIX_OFFSET = 14;
const int NOT_EMPTY = 1;
const int NOT_EMPTY_POSITION = 12;
const int BYTE_SIZE = 8;
const int MAX_COLOR = 255;
const int MIN_COLOR = 0;
const int GAISSIAN_BLUR = 6;

const double GRAY_SCL_RED = 0.299;
const double GRAY_SCL_GREEN = 0.587;
const double GRAY_SCL_BLUE = 0.114;

const std::vector<char> BMP_FORMAT = {'B', 'M'};
const std::vector<int> BYTES_TO_NUM_OFFSETS = {8, 16, 24};
const std::vector<std::vector<int>> MATRIX_FOR_SHARP = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const std::vector<std::vector<int>> MATRIX_FOR_EDGE = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}  // namespace magic