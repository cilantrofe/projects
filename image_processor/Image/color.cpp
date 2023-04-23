#include "color.h"

Color::Color(uint8_t blue, uint8_t green, uint8_t red) : blue(blue), green(green), red(red) {
}

void Color::SetColor(uint8_t blue_new, uint8_t green_new, uint8_t red_new) {
    blue = blue_new;
    green = green_new;
    red = red_new;
}