#include "Explosion.h"
#include <allegro5/allegro_primitives.h>

void Explosion::update() {
    if (al_get_time() - explosionTimer < _durationSecs) {
        _radius += _amount;
    } else {
        // Remove the explosion
        remove = true;
    }
}

void Explosion::render() {
    al_draw_circle(_x, _y, _radius * 2, al_map_rgb_f(1, 0, 0), 1);
    al_draw_filled_circle(_x, _y, _radius, al_map_rgb_f(1, 0, 0));
}

void Explosion::dispose() {

}

