#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Bullet.h"
#include <vector>

class Enemy {
public:
	Enemy(int star_);
	void init();
    void update(float playerX, float playerY);
	void render();
	void dispose();

    float getX() { return x; }
    float getY() { return y; }
    float getRadius() { return radius; }
    void hit();
    int getLives() { return lives; }

    std::vector<Bullet*> getBullets() { return bullets; }

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

    ALLEGRO_SAMPLE* hitSound;
    ALLEGRO_SAMPLE_ID hitSoundID;

    std::vector<Bullet*> bullets;

};
