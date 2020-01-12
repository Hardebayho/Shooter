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
	float angle = (rand() % 140 + 29) * 3.1415 / 180;
	dx = -abs(cos(angle) * speed);
	dy = sin(angle) * speed;
    if (dy == 0) dy = -1 * speed;
	ready = false;
    pulseAlpha = 1;
    hitColor = al_color_name("white");
    hitTimer = 0;
    hitTimerDiff = 2;
    recovering = false;

    hitSound = al_load_sample("res/sounds/enemy_hit.wav");
    if (!hitSound)
        std::cout << "Could not load the enemies' hit sound." << std::endl;
}

void Enemy::hit() {
    lives--;
    hitTimer = al_get_time();
    recovering = true;

    if (lives > 0)
        al_play_sample(hitSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, &hitSoundID);

}

void Enemy::update(float playerX, float playerY) {
	
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

    // Use a random number to determine if we should shoot.
    // We'll use the player position to determine the angle.
    if (star > 2) {
        float num = (rand() % 500);
        if (num == 4) {
            // spawn a new enemy bullet
            Bullet* bullet = new Bullet(x, y);
            float dx, dy;
            float angle = atan2(playerY - y, playerX - x);
            dx = cos(angle);
            dy = sin(angle);

            bullet->setSpeed(5);
            bullet->setDX(dx * bullet->getSpeed());
            bullet->setDY(dy * bullet->getSpeed());
            bullet->setColor(al_map_rgb_f(1, 0, 0));
            bullet->setInsideColor(al_map_rgb_f(0, 1, 0));
            bullets.push_back(bullet);
        }
    }

    for (auto &b : bullets) {
        b->update();
    }

    for (std::vector<Bullet*>::iterator bulletsIter = bullets.begin(); bulletsIter != bullets.end();) {
        if (!(*bulletsIter)->isAlive()) {
            (*bulletsIter)->dispose();
            delete (*bulletsIter);
            bulletsIter = bullets.erase(bulletsIter);
        } else bulletsIter++;
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

    // Draw enemy bullets
    for (auto& bullet : bullets) {
        bullet->render();
    }
}

void Enemy::dispose() {
    al_destroy_sample(hitSound);
    for (auto& b : bullets) {
        b->dispose();
        delete b;
    }
    bullets.clear();
}
