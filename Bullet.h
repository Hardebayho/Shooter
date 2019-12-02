#pragma once
#include <allegro5/allegro_primitives.h>

class Bullet {
public:
	Bullet(float x, float y);
	void init();
	void update();
	void render();
	void dispose();
	
	bool isAlive() { return alive; }
    float getX() { return x; }
    float getY() { return y; }
    float getRadius() { return radius; }
    void kill() { alive = false; }

private:
	float x;
	float y;
	float radius;
	float dx;
	bool alive;

};
