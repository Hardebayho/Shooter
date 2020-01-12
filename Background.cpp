#include "Background.h"
#include "Constants.h"

Background::Background(std::string filepath)
{
    image = al_load_bitmap(filepath.c_str());
    x = 0;
    y = 0;
}

void Background::update() {
    x -= 1.2;
    if (x < -DISPLAY_WIDTH) x = 0;
}

void Background::render() {
    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), DISPLAY_WIDTH + x, y, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
}

void Background::dispose() {
    al_destroy_bitmap(image);
}
