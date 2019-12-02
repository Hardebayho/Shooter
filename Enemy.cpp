#include "Enemy.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "Constants.h"

Enemy::Enemy(int star_) : star(star_) {
	init();
}

void Enemy::init() {
	switch (star) {
		case 1:
            speed = 2;
			radius = 10;
			lives = 1;
			color = al_map_rgb_f(0.6, 0.4, 0.6);
		break;
		case 2:
            speed = 3;
			radius = 10;
			lives = 2;
			color = al_map_rgb_f(0.4, 0.6, 0.6);
		break;
		case 3:
            speed = 4;
			radius = 10;
			lives = 3;
			color = al_map_rgb_f(0.6, 0.6, 0.4);
		break;
		case 4:
            speed = 6;
			radius = 10;
			lives = 5;
			color = al_map_rgb_f(0.3, 0.4, 0.6);
		break;
		case 5:
            speed = 10;
			radius = 10;
			lives = 8;
			color = al_map_rgb_f(0.4, 0.6, 0.3);
		break;
	}
	x = DISPLAY_WIDTH;
	y = rand() % (DISPLAY_HEIGHT - (int)radius);
	float angle = (rand() % 140 + 29) * 3.1415 / 180;
	dx = -abs(cos(angle) * speed);
	dy = sin(angle) * speed;
	ready = false;
    pulseAlpha = 1;
}

void Enemy::update() {
	
	if (!ready) {
        if (x > 0 && x < DISPLAY_WIDTH - radius && y > 0 && y < DISPLAY_HEIGHT - radius) ready = true;
	}

	x += dx;
	y += dy;

    pulseAlpha -= 0.026;
    if (pulseAlpha < 0) pulseAlpha = 1;
	
	if (ready) {
		// Do bounds checking
		if (x < radius || x > DISPLAY_WIDTH - radius) dx = -dx;
		if (y < radius || y > DISPLAY_HEIGHT - radius) dy = -dy;
	}
}

void Enemy::render() {
	al_draw_circle(x, y, radius, color, 2);
    al_draw_filled_circle(x, y, radius / 2, al_map_rgba_f(1 * pulseAlpha, 1 * pulseAlpha, 0 * pulseAlpha, pulseAlpha));
}

void Enemy::dispose() {

}
