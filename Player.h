#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Bullet.h"
#include <vector>
#include <allegro5/allegro_font.h>

class Player {

public:
	Player();
	void init();
	void update();
	void handleInput();
	void render();
	void dispose();

    float getX() { return x; }
    float getY() { return y; }
    float getRadius() { return radius; }
    void loseLife() { lives--; }

    std::vector<Bullet*> getBullets() { return bullets; }
	
private:
	float x;
	float y;
	float radius;
	float dx;
	float dy;
	float moveSpeed;
    int lives;
	
	// Movement
	bool left;
	bool right;
	bool up;
	bool down;
	bool firing;
	
	float firingTimer;
	float firingTimerDiff;
	
	ALLEGRO_KEYBOARD_STATE key_state;
	
	std::vector<Bullet*> bullets;
	ALLEGRO_FONT* numBulletsFont;

    float pulseAlpha;

};










