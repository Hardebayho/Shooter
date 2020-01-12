#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "Constants.h"
#include "Player.h"
#include <math.h>
#include <vector>
#include "Enemy.h"
#include "CollisionManager.h"
#include "Explosion.h"
#include "Background.h"

void update();
void render();
void handleInput();
void disposeEntities();
void dispose();

bool running;
bool redraw;

ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;

ALLEGRO_FONT *gameFont = nullptr;

Player player;
ALLEGRO_SAMPLE* playerDeadSound;
ALLEGRO_SAMPLE_ID playerDeadSoundID;

ALLEGRO_AUDIO_STREAM* backgroundMusic;
ALLEGRO_AUDIO_STREAM* gameOverMusic;

std::vector<Enemy*> enemies;
ALLEGRO_SAMPLE* enemyDeadSound;
ALLEGRO_SAMPLE_ID enemyDeadSoundID;
CollisionManager collisionManager;

std::vector<Explosion*> explosions;

Background* background;

// Level information.

int level;
int levelProgress;
int maxLevelProgress;
float levelProgressAlpha;
bool levelStart;

// End level information

void initLevel();

int main() {

	if (!al_init())
		return -1;
	
    al_install_audio();
    al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
    al_init_acodec_addon();
    al_init_image_addon();
	
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

                initLevel();

                al_reserve_samples(10);

                backgroundMusic = al_load_audio_stream("res/music/Electron.ogg", 4, 2048);
                al_attach_audio_stream_to_mixer(backgroundMusic, al_get_default_mixer());
                al_set_audio_stream_playmode(backgroundMusic, ALLEGRO_PLAYMODE_LOOP);

                gameOverMusic = al_load_audio_stream("res/music/breves_dies_hominis.ogg", 4, 2048);
                al_attach_audio_stream_to_mixer(gameOverMusic, al_get_default_mixer());
                al_set_audio_stream_playmode(gameOverMusic, ALLEGRO_PLAYMODE_LOOP);
                al_set_audio_stream_playing(gameOverMusic, false);

                enemyDeadSound = al_load_sample("res/sounds/enemy_dead.ogg");
                playerDeadSound = al_load_sample("res/sounds/player_dead.wav");

                gameFont = al_create_builtin_font();
                background = new Background("res/graphics/stars.jpg");

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

void initLevel() {
    level = 0;
    levelProgress = 1;
    maxLevelProgress = 4;
    levelProgressAlpha = 1;
    levelStart = false;
}

void update() {

    background->update();

    // Update player
    player.update();

    if (player.getLives() <= 0) {
        ALLEGRO_KEYBOARD_STATE key_state;
        al_get_keyboard_state(&key_state);
        if (al_key_down(&key_state, ALLEGRO_KEY_LCTRL)) {
            disposeEntities();
            initLevel();
            player.init();
            // Reset sounds too
            al_set_audio_stream_playing(backgroundMusic, true);
            al_set_audio_stream_playing(gameOverMusic, false);
        }
        return;
    }

    // Let's know if we need to put enemies on the screen
    if (enemies.size() <= 0) {
        if (level <= 0 || levelProgress > maxLevelProgress) {
            level++;
            levelProgress = 1;
            levelStart = false;
        } else if (levelProgress <= maxLevelProgress && levelStart) {
            levelProgress++;
            levelStart = false;
        }
    }

    // If we're still drawing our text to the screen,
    // Make sure to update the levelProgressAlpha variable
    if (!levelStart) {
        levelProgressAlpha -= 0.005;
        if (levelProgressAlpha <= 0) {
            levelProgressAlpha = 1;
            levelStart = true;
        }
    }

    if (enemies.size() <= 0 && levelStart) {
        switch (level) {
            case 1:
                switch (levelProgress) {
                    case 1:
                        for (int i = 0; i < 8; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                    break;
                    case 2:
                        for (int i = 0; i < 12; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                        for (int i = 0; i < 2; i++) {
                            enemies.push_back(new Enemy(2));
                        }
                    break;
                    case 3:
                        for (int i = 0; i < 10; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                        for (int i = 0; i < 4; i++) {
                            enemies.push_back(new Enemy(2));
                        }
                    break;
                    case 4:
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(2));
                        }
                    break;
                }
            break;
            case 2:
                switch (levelProgress) {
                    case 1:
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(3));
                        }
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                    break;
                    case 2:
                        for (int i = 0; i < 3; i++) {
                            enemies.push_back(new Enemy(3));
                        }
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(2));
                        }
                    break;
                    case 3:
                        for (int i = 0; i < 4; i++) {
                            enemies.push_back(new Enemy(2));
                        }
                        for (int i = 0; i < 8; i++) {
                            enemies.push_back(new Enemy(1));
                        }
                    break;
                    case 4:
                        for (int i = 0; i < 5; i++) {
                            enemies.push_back(new Enemy(3));
                        }
                        for (int i = 0; i < 2; i++) {
                            enemies.push_back(new Enemy(4));
                        }
                    break;
                }
            break;
            case 3:
                switch (levelProgress) {
                    case 1:
                    break;
                    case 2:
                    break;
                    case 3:
                    break;
                    case 4:
                    break;
                }
            break;
            case 4:
                switch (levelProgress) {
                    case 1:
                    break;
                    case 2:
                    break;
                    case 3:
                    break;
                    case 4:
                    break;
                }
            break;
        }
    }
	
    // Update enemy
	for (auto& enemy : enemies) {
        enemy->update(player.getX(), player.getY());
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
                        al_play_sample(enemyDeadSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, &enemyDeadSoundID);
                    explosions.push_back(new Explosion(enemyX, enemyY, enemyRadius, 0.2, 1));
                }
        }
    }

    // Player - Enemies
    if (!player.isRecovering())
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
                // Check for dead player
                if (player.getLives() <= 0) {
                    al_play_sample(playerDeadSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, &playerDeadSoundID);
                    al_set_audio_stream_playing(backgroundMusic, false);
                    al_set_audio_stream_playing(gameOverMusic, true);
                }
            }
        }

    // Player - Enemy bullets
    if (!player.isRecovering())
        for (auto& enemy : enemies) {
            for (auto& bullet : enemy->getBullets()) {
                if (collisionManager.checkCircleCollision(player.getX(), player.getY(), player.getRadius(), bullet->getX(), bullet->getY(), bullet->getRadius())) {
                    player.loseLife();
                    bullet->kill();
                    // Check for dead player
                    if (player.getLives() <= 0) {
                        al_play_sample(playerDeadSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, &playerDeadSoundID);
                        al_set_audio_stream_playing(backgroundMusic, false);
                        al_set_audio_stream_playing(gameOverMusic, true);
                    }
                }
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
    for (std::vector<Explosion*>::iterator explosionsIterator = explosions.begin(); explosionsIterator != explosions.end(); explosionsIterator++) {
        if ((*explosionsIterator)->removeExplosion()) {
            delete (*explosionsIterator);
            explosions.erase(explosionsIterator);
            explosionsIterator--;
        }
    }

}

void render() {

    al_clear_to_color(al_map_rgb_f(0, 0, 0));

    // Draw the game background
    background->render();
	
	// Render all stuff here...
    if (!levelStart) {
        al_draw_textf(gameFont, al_map_rgba_f(1 * levelProgressAlpha, 1 * levelProgressAlpha, 1 * levelProgressAlpha, levelProgressAlpha), DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, " - LEVEL %i : %i -", level, levelProgress);
    }


    if (player.getLives() > 0)
        player.render();

    if (levelProgress >= maxLevelProgress) {
        // Display the level progress info
    }
	
	for (auto& enemy : enemies) {
		enemy->render();
	}

    for (auto& explosion : explosions) {
        explosion->render();
    }

    // Draw game over
    if (player.getLives() <= 0)
        al_draw_multiline_text(gameFont, al_map_rgb_f(1, 1, 1), DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, DISPLAY_HEIGHT, 50, ALLEGRO_ALIGN_CENTER, "- G A M E  O V E R! -\nPress Left Control Key to Restart");
	
	al_flip_display();
}

void handleInput() {
	player.handleInput();
}

void disposeEntities() {
    // Dispose of player resources
    player.dispose();

    // Remove and delete all enemies
    for (auto& enemy : enemies) {
        enemy->dispose();
        delete enemy;
    }
    enemies.clear();

    // Remove and delete all the explosions
    for (auto& explosion : explosions) {
        explosion->dispose();
        delete explosion;
    }
}

void dispose() {

    disposeEntities();

    background->dispose();
    delete background;

    al_destroy_sample(enemyDeadSound);
    al_destroy_sample(playerDeadSound);
    al_destroy_audio_stream(backgroundMusic);
    al_destroy_audio_stream(gameOverMusic);

    // Destroy allegro objects.
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}
