add_executable(
        image_processor
        image_processor.cpp
        "Image/color.h"
        Image/image.h
        Image/image.cpp
        Image/color.cpp
        Read_and_Write/read.h
        Read_and_Write/read.cpp
        Read_and_Write/magic.h
        Read_and_Write/write.h
        Read_and_Write/write.cpp
        Filters/filter.h
        Filters/filter.cpp Filters/crop.h Filters/crop.cpp Filters/sharpening.h Filters/sharpening.cpp Filters/negative.h Filters/negative.cpp Filters/gray_scale.h Filters/gray_scale.cpp Filters/gaissian_blur.h Filters/gaissian_blur.cpp Filters/edge_detection.h Filters/edge_detection.cpp)
