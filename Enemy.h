#pragma once
#include <allegro5/allegro.h>

class Enemy {
public:
	Enemy(int star_);
	void init();
	void update();
	void render();
	void dispose();

    float getX() { return x; }
    float getY() { return y; }
    float getRadius() { return radius; }
    void hit() { lives--; }
    int getLives() { return lives; }

private:
	int star; // This one's for the player's power
	float x;
	float y;
	float radius;
	float speed;
	float dx;
	float dy;
	float lives;
	bool ready;
	ALLEGRO_COLOR color;
    float pulseAlpha;
};
