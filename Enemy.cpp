#include "Enemy.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "Constants.h"
#include <iostream>

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
    x = DISPLAY_WIDTH - radius;
    y = abs(rand() % (DISPLAY_HEIGHT - (int)radius));
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "An enemy's x: " << x << std::endl;
    std::cout << "An enemy's y: " << y << std::endl;
	float angle = (rand() % 140 + 29) * 3.1415 / 180;
	dx = -abs(cos(angle) * speed);
	dy = sin(angle) * speed;
    std::cout << "An enemy's dx: " << dx << std::endl;
    std::cout << "An enemy's dy: " << dy << std::endl;
    std::cout << "----------------------------------------" << std::endl;
	ready = false;
    pulseAlpha = 1;
    hitColor = al_color_name("white");
    hitTimer = 0;
    hitTimerDiff = 2;
    recovering = false;
}

void Enemy::update() {
	
	if (!ready) {
        if (x > 0 && x < DISPLAY_WIDTH - radius) ready = true;
	}

    // Enemy got hit
    if (hitTimer > 0 && recovering) {
        if (al_get_time() - hitTimer >= hitTimerDiff) {
            hitTimer = 0;
            recovering = false;
        }
    }

	x += dx;
	y += dy;

    pulseAlpha -= 0.03;
    if (pulseAlpha < 0) pulseAlpha = 1;
	
	if (ready) {
		// Do bounds checking
		if (x < radius || x > DISPLAY_WIDTH - radius) dx = -dx;
		if (y < radius || y > DISPLAY_HEIGHT - radius) dy = -dy;
	}
}

void Enemy::render() {

    if (recovering) {
        al_draw_circle(x, y, radius, hitColor, 2);
        al_draw_filled_circle(x, y, radius / 2, hitColor);
    } else {
        al_draw_circle(x, y, radius, color, 2);
        al_draw_filled_circle(x, y, radius / 2, al_map_rgba_f(1 * pulseAlpha, 1 * pulseAlpha, 0 * pulseAlpha, pulseAlpha));
    }
}

void Enemy::dispose() {

}
