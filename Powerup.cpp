#include "Powerup.h"
#include <allegro5/allegro.h>
#include "Constants.h"

Powerup::Powerup(PowerupType type, float x, float y)
{
    this->type = type;
    this->x = x;
    this->y = y;
    init();
}

void Powerup::init() {
    switch (type) {
        case EXTRA_LIFE:
            image = al_load_bitmap("");
        break;
        case EXTRA_BULLET:
            image = al_load_bitmap("");
        break;
        case WAVE_WIPE:
            image = al_load_bitmap("");
        break;
    }
    alive = true;
    width = al_get_bitmap_width(image);
    height = al_get_bitmap_height(image);
}

void Powerup::update() {
    x -= 5;
    if (x < 0)
        alive = false;
}

void Powerup::render() {
    al_draw_bitmap(image, x, y, 0);
}

void Powerup::dispose() {
    al_destroy_bitmap(image);
}
