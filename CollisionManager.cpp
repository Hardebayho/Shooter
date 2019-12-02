#include "CollisionManager.h"
#include <math.h>

CollisionManager::CollisionManager()
{

}

bool CollisionManager::checkCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist <= r1 + r2)
        return true; // Collision has occurred

    return false;
}
