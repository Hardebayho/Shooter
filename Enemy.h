#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

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
    void hit() {
        lives--;
        hitTimer = al_get_time();
        recovering = true;
    }
    int getLives() { return lives; }

    bool isRecovering() { return recovering; }

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

    ALLEGRO_COLOR hitColor;
    float hitTimer;
    float hitTimerDiff;
    bool recovering;
};
