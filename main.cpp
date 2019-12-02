#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "Constants.h"
#include "Player.h"
#include <math.h>
#include <vector>
#include "Enemy.h"
#include "CollisionManager.h"
#include "Explosion.h"

void update();
void render();
void handleInput();
void dispose();

bool running;
bool redraw;

ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;

Player player;

std::vector<Enemy*> enemies;
CollisionManager collisionManager;

std::vector<Explosion*> explosions;

int main() {

	if (!al_init())
		return -1;
	
	al_init_primitives_addon();
	al_init_font_addon();
	al_install_keyboard();
	
	ALLEGRO_EVENT event;

    al_set_new_window_position(0, 0);
	
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display) {
		std::cout << "Could not create the display. Exiting..." << std::endl;
	} else {
		event_queue = al_create_event_queue();
		
		if (!event_queue) {
			std::cout << "Could not create the event queue. Exiting..." << std::endl;
			al_destroy_display(display);
		} else {
			timer = al_create_timer(1.0/60);
			if (!timer) {
				std::cout << "Could not create the timer. Exiting..." << std::endl;
				al_destroy_display(display);
				al_destroy_event_queue(event_queue);
			} else {
				// Register event sources
				al_register_event_source(event_queue, al_get_display_event_source(display));
				al_register_event_source(event_queue, al_get_timer_event_source(timer));
				al_register_event_source(event_queue, al_get_keyboard_event_source());
				
				running = true;
				redraw = true;
				
				srand(time(NULL));
				
				// Initialize all objects here
                for (int i = 0; i < 16; i++) {
                    enemies.push_back(new Enemy(1));
				}
				player.init();
				
				al_start_timer(timer);
				while (running) {
					al_wait_for_event(event_queue, &event);
					
					switch (event.type) {
						case ALLEGRO_EVENT_DISPLAY_CLOSE:
							running = false;
						break;
						case ALLEGRO_EVENT_TIMER:
							handleInput();
							update();
							redraw = true;
						break;
					}
					
					if (redraw && al_is_event_queue_empty(event_queue)) {
						redraw = false;
						render();
					}
				}
				
				dispose();
			}
		}
	}
	
	return 0;
	
}

void update() {
    // Update player
	player.update();
	
    // Update enemy
	for (auto& enemy : enemies) {
		enemy->update();
	}

    // update explosions
    for (auto& explosion : explosions) {
        explosion->update();
    }

    // Check for collisions.
    // Bullet - Enemy
    for (auto& bullet : player.getBullets()) {
        for (auto& enemy : enemies) {
            float enemyX = enemy->getX();
            float enemyY = enemy->getY();
            float enemyRadius = enemy->getRadius();
            if (!enemy->isRecovering())
            if (collisionManager.checkCircleCollision(bullet->getX(), bullet->getY(), bullet->getRadius(), enemyX, enemyY, enemyRadius)) {
                bullet->kill();
                enemy->hit();
                if (enemy->getLives() <= 0)
                    explosions.push_back(new Explosion(enemyX, enemyY, enemyRadius, 0.2, 1));
            }
        }
    }

    // Player - Enemies
    for (auto& enemy : enemies) {
        float enemyX = enemy->getX();
        float enemyY = enemy->getY();
        float enemyRadius = enemy->getRadius();

        float playerX = player.getX();
        float playerY = player.getY();
        float playerRadius = player.getRadius();

        if (collisionManager.checkCircleCollision(playerX, playerY, playerRadius, enemyX, enemyY, enemyRadius)) {
            player.loseLife();
            enemy->hit();
        }
    }

    // Check for and delete removable enemies
    for (std::vector<Enemy*>::iterator enemiesIter = enemies.begin(); enemiesIter != enemies.end(); ++enemiesIter) {
        if ((*enemiesIter)->getLives() <= 0) {
            delete (*enemiesIter);
            enemies.erase(enemiesIter);
            enemiesIter--;
        }
    }

    // Check for removable explosions
    for (std::vector<Explosion*>::iterator explosionsIterator = explosions.begin(); explosionsIterator != explosions.end(); ++explosionsIterator) {
        if ((*explosionsIterator)->removeExplosion()) {
            delete (*explosionsIterator);
            explosions.erase(explosionsIterator);
            explosionsIterator--;
        }
    }

}

void render() {
    al_clear_to_color(al_map_rgb_f(0, 0, 0));
	
	// Render all stuff here...
	player.render();
	
	for (auto& enemy : enemies) {
		enemy->render();
	}

    for (auto& explosion : explosions) {
        explosion->render();
    }
	
	al_flip_display();
}

void handleInput() {
	player.handleInput();
}

void dispose() {

	player.dispose();
	
	for (auto& enemy : enemies) {
		enemy->dispose();
		delete enemy;
	}
	
	enemies.clear();

    for (auto& explosion : explosions) {
        explosion->dispose();
        delete explosion;
    }

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}













