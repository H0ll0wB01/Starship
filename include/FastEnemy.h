#ifndef FASTENEMY_H
#define FASTENEMY_H


#include "Enemy.h"
class FastEnemy :public Enemy
{
public:
    // Constructor and destructor
    FastEnemy();
    FastEnemy(float posX, float posY);
    virtual ~FastEnemy();

    // initializers
    void initVariables() override;

    void initTexture() override;

    void initSprite() override;

    // Enemy Behaviour

    void Move() override;
    void Update() override;
};

#endif // !FASTENEMY_H
