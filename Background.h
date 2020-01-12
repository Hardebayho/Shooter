#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <allegro5/allegro_image.h>
#include <string>
#include <allegro5/allegro.h>

class Background
{
public:
	Background(std::string filepath);
	void update();
	void render();
	void dispose();

private:
	float x;
	float y;
	ALLEGRO_BITMAP* image;
};

#endif // BACKGROUND_H
