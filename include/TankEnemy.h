#ifndef TANKENEMY_H
#define TANKENEMY_H

#include "Enemy.h"

class TankEnemy : public Enemy
{
public:
    // Constructor and destructor
    TankEnemy();
    TankEnemy(float posX, float posY);
    virtual ~TankEnemy();

    // initializers
    void initVariables() override;

    void initTexture() override;

    void initSprite() override;
};


#endif // !DEFAULTENEMY
