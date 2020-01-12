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

    float getDX() { return dx; }
    float getDY() { return dy; }

    void setDX(float dx) { this->dx = dx; }
    void setDY(float dy) { this->dy = dy; }

    void setSpeed(float speed) { this->speed = speed; }
    float getSpeed() { return speed; }

    void setColor(ALLEGRO_COLOR color) { bulletColor = color; }
    ALLEGRO_COLOR getColor() { return bulletColor; }
    ALLEGRO_COLOR getInsideColor() { return insideColor; }
    void setInsideColor(ALLEGRO_COLOR color) { insideColor = color; }

private:
	float x;
	float y;
	float radius;
	float dx;
    float dy;
    float speed;
	bool alive;
    ALLEGRO_COLOR bulletColor;
    ALLEGRO_COLOR insideColor;

};
