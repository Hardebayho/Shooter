#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <allegro5/allegro.h>

class Explosion
{
public:
	/**
	 * @brief Explosion constructor. Makes an explosion object
	 * @param x - x position of the object to explode
	 * @param y - y position of the object to explode
	 * @param width - Width of the object to explode.
	 * @param height - Height of the object to explode.
	 * @param durationSecs - How long the explosion should stay on the screen
	 * @param amount - Amount to increase the radius of the explosion by
	 */
	Explosion(float x, float y, float radius, float durationSecs, float amount) : _x(x), _y(y), _radius(radius), _durationSecs(durationSecs), _amount(amount) {
		explosionTimer = al_get_time();
		remove = false;
	}
	void update();
	void render();
	bool removeExplosion() { return remove; }
	void dispose();

private:
	float _x;
	float _y;
	float _radius;
	float _durationSecs;
	float explosionTimer;
	float _amount;
	bool remove;

};

#endif // EXPLOSION_H
