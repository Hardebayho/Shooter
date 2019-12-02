project(Shooter)

add_executable(Shooter main.cpp Player.cpp Bullet.cpp Enemy.cpp CollisionManager.cpp Explosion.cpp)

target_link_libraries(Shooter allegro allegro_primitives allegro_font allegro_color)
