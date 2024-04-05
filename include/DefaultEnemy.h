#ifndef DEFAULTENEMY_H
#define DEFAULTENEMY_H

#include "Enemy.h"

class DefaultEnemy : public Enemy
{
    public:
        // Constructor and destructor
        DefaultEnemy();
        DefaultEnemy(float posX, float posY);
        virtual ~DefaultEnemy();

        // initializers
        void initVariables() override;
       
        void initTexture() override;

        void initSprite () override;
    
};

#endif // !DEFAULTENEMY