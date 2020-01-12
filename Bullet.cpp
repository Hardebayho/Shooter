#include "Bullet.h"
#include "Constants.h"

Bullet::Bullet(float x_, float y_) : x(x_), y(y_) {
	init();
}

void Bullet::init() {
    speed = 12;
    dx = speed;
    dy = 0;
    radius = 4;
	alive = true;
    bulletColor = al_map_rgb_f(0, 0, 1);
    insideColor = al_map_rgb_f(0, 1, 1);
}

void Bullet::update() {
	x += dx;
    y += dy;
    alive = x < DISPLAY_WIDTH && x > 0 && y < DISPLAY_HEIGHT && y > 0;
}

void Bullet::render() {
    al_draw_circle(x, y, radius, bulletColor, 1);
    al_draw_filled_circle(x, y, radius / 2, insideColor) ;
}

void Bullet::dispose() {

}
