#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H


class CollisionManager
{
public:
    CollisionManager();
    /** Checks collision between two circles */
    bool checkCircleCollision(float x1, float y1, float r1, float x2, float y2, float r2);
};

#endif // COLLISIONMANAGER_H
