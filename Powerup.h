#ifndef POWERUP_H
#define POWERUP_H
#include <allegro5/allegro_image.h>

enum PowerupType {
	EXTRA_LIFE, // Gives the player an extra life.
	EXTRA_BULLET, // Adds an extra bullet to the player's arsenal
	WAVE_WIPE // This one will be extremely rare
};

class Powerup
{
public:
	Powerup(PowerupType type, float x, float y);
	void init();
	void update();
	void render();
	void dispose();

	bool isAlive() { return alive; }
	int getWidth() { return width; }
	int getHeight() { return height; }

private:
	float x;
	float y;
	int width;
	int height;
	ALLEGRO_BITMAP* image;
	PowerupType type;
	bool alive;
};

#endif // POWERUP_H
