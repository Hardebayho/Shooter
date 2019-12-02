#include "Bullet.h"
#include "Constants.h"

Bullet::Bullet(float x_, float y_) : x(x_), y(y_) {
	init();
}

void Bullet::init() {
	dx = 12;
    radius = 4;
	alive = true;
}

void Bullet::update() {
	x += dx;
	alive = x < DISPLAY_WIDTH;
}

void Bullet::render() {
	al_draw_circle(x, y, radius, al_map_rgb_f(1, 0, 0), 1);
	al_draw_filled_circle(x, y, radius / 2, al_map_rgb_f(1, 1, 1));
}

void Bullet::dispose() {

}
