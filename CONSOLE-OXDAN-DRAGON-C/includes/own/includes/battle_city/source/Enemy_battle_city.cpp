#include "Enemy_battle_city.h"
#include "Tank_battle_city.h"
#include "../../../all_diclarations.h"
extern bool sliding_8;

Enemy_1::Enemy_1(const float &x, const float &y)
    : Tank(x, y, 39, 39, oxdan_dragon_c + "/includes/own/includes/battle_city/media/enemySprites.png"), timeBeforeMoving(0.f), timeBeforeShot(0.f) {

    buffer_dead_4.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/fire.wav");

    // Create an instance of sf::Sound and set its buffer to the loaded sound buffer

    sound_dead_4.setBuffer(buffer_dead_4);

    sound_dead_4.setVolume(80);

    sf::Sound sound_dead_4;
    sound_dead_4.setBuffer(buffer_dead_4);
    sound_dead_4.setVolume(80);
}

void Enemy_1::move(const sf::Int64 &time) {
    mSpeed = 0.05f;

    timeBeforeMoving += time;

    if (timeBeforeMoving > 1000 + rand() % 501) {
        mDir = rand() % 4;
        timeBeforeMoving = 0.f;
    }

    switch (mDir) {
        case 0:
            mDx = mSpeed;
            mDy = 0;
            break;

        case 1:
            mDx = -mSpeed;
            mDy = 0;
            break;

        case 2:
            mDx = 0;
            mDy = mSpeed;
            break;

        case 3:
            mDx = 0;
            mDy = -mSpeed;
            break;
    }
    if (mCollision) tank_interaction();
    mX += mDx * time;
    mY += mDy * time;
}

void Enemy_1::shoot(const float &time) {
    timeBeforeShot += time;
    
    if (timeBeforeShot > 1000.f) {
        if (!bullet.present)
            if (rand() % 2)
            {
               
                sound_dead_4.play();
                bullet.present = true;
            }
            

        timeBeforeShot = 0.f;
    }
}

void Enemy_1::update(const sf::Int64 &time, Map &map, const bool &collision) {
    mCollision = collision;
    move(time);

    mSpeed = 0.f;
    mSprite.setPosition(mX, mY);
    animate(time);
    map_interaction(map);

    bullet.update(map, time, mX, mY, mDir);
    shoot(time);
}
