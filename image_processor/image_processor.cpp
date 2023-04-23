#include <iostream>
#include "Image/image.h"
#include "Read_and_Write/read.h"
#include "Read_and_Write/write.h"
#include "Filters/filter.h"
#include "Filters/gray_scale.h"
#include "Filters/edge_detection.h"
#include "Filters/gaissian_blur.h"
#include "Filters/negative.h"
#include "Filters/sharpening.h"
#include "Filters/crop.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }
    std::string input_file = argv[1];
    std::string output_file = argv[2];

    write_and_read::Reader reader(input_file);
    Image image = reader.ReadFile();
    for (int i = 3; i < argc; ++i) {
        std::string argument = argv[i];
        if (argument == "-gs") {
            image = GrayScale().App(image);
        } else if (argument == "-edge") {
            if (i + 1 < argc) {
                int threshold = std::stoi(argv[i + 1]);
                image = EdgeDetection(threshold).App(image);
                i += 1;
            } else {
                throw std::runtime_error("No parameter");
            }
        } else if (argument == "-blur") {
            double sigma = std::stod(argv[i + 1]);
            image = GaissianBlur(sigma).App(image);
        } else if (argument == "-neg") {
            image = Negative().App(image);
        } else if (argument == "-sharp") {
            image = Sharpening().App(image);
        } else if (argument == "-crop" && i + 2 < argc) {
            size_t width = std::stoi(argv[++i]);
            size_t height = std::stoi(argv[++i]);
            if (width > 0 && height > 0) {
                image = Crop(width, height).App(image);
            } else {
                throw std::runtime_error("Missing parameters");
            }
        }
    }
    write_and_read::Writer writer(output_file);

    writer.WriteImage(image);

    return 0;
}