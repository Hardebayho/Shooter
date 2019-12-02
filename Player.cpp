#include "Player.h"
#include "Constants.h"

Player::Player() {}

void Player::init() {
	x = 20;
	y = DISPLAY_HEIGHT / 2;
	radius = 10;
	dx = dy = 0;
	moveSpeed = 6;
	
	left = right = up = down = false;
	firing = false;
	firingTimer = al_get_time();
	firingTimerDiff = 0.2;
	numBulletsFont = al_create_builtin_font();
    pulseAlpha = 1;
    lives = 3;
}

void Player::update() {
	if (left) {
		dx = -moveSpeed;
	} else if (right) {
		dx = moveSpeed;
	} else {
		dx = 0;
	}
	
	if (up) {
		dy = -moveSpeed;
	} else if (down) {
		dy = moveSpeed;
	} else {
		dy = 0;
	}

    // Check for objects to remove
    // Bullets
    for (std::vector<Bullet*>::iterator iter = bullets.begin(); iter != bullets.end(); ++iter) {
        if (!(*iter)->isAlive()) {
            (*iter)->dispose();
            delete (*iter);
            bullets.erase(iter);
            iter--;
        }
    }
	
	if (firing) {
		if (al_get_time() - firingTimer >= firingTimerDiff) {
			bullets.push_back(new Bullet(x, y));
			firingTimer = al_get_time();
		}
	}
	
	for (auto& bullet : bullets) {
		bullet->update();
	}
	
	x += dx;
	y += dy;

    pulseAlpha -= 0.016;
    if (pulseAlpha < 0) pulseAlpha = 1;
	
	if (x < radius) x = radius;
	if (x > DISPLAY_WIDTH - radius) x = DISPLAY_WIDTH - radius;
	
	if (y < radius) y = radius;
	if (y > DISPLAY_HEIGHT - radius) y = DISPLAY_HEIGHT - radius;
}

void Player::handleInput() {
	al_get_keyboard_state(&key_state);
	
	if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
		left = true;
		right = false;
	} else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
		right = true;
		left = false;
	} else {
		left = right = false;
	}
	
	if (al_key_down(&key_state, ALLEGRO_KEY_UP)) {
		up = true;
		down = false;
	} else if (al_key_down(&key_state, ALLEGRO_KEY_DOWN)) {
		down = true;
		up = false;
	} else {
		up = down = false;
	}
	
	if (al_key_down(&key_state, ALLEGRO_KEY_SPACE)) {
		firing = true;
	} else {
		firing = false;
	}
}

void Player::render() {
	al_draw_circle(x, y, radius, al_map_rgb_f(0, 1, 0.2), 2);
    al_draw_filled_circle(x, y, radius / 2, al_map_rgba_f(1 * pulseAlpha, 1 * pulseAlpha, 1 * pulseAlpha, pulseAlpha));
	
    al_draw_textf(numBulletsFont, al_map_rgb_f(1, 1, 1), 10, 10, 0, "Num Bullets: %i", (int)bullets.size());
	
	for (auto& bullet : bullets) {
		bullet->render();
	}

    // Draw lives
    for (int i = 0; i < lives; i++) {
        al_draw_circle(i * 24 + 20, 60, radius, al_map_rgb_f(0, 1, 0.2), 2);
        al_draw_filled_circle(i * 24 + 20, 60, radius / 2, al_map_rgba_f(1 * pulseAlpha, 1 * pulseAlpha, 1 * pulseAlpha, pulseAlpha));
    }
}

void Player::dispose() {
	for (auto& bullet : bullets) {
		bullet->dispose();
		delete bullet;
	}
	
	bullets.clear();
	al_destroy_font(numBulletsFont);
}
