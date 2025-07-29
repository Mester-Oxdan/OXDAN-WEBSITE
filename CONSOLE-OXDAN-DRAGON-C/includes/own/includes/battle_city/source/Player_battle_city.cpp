#include <SFML/Window/Keyboard.hpp>
#include "Player_battle_city.h"
#include "Tank_battle_city.h"
#include "Map_battle_city.h"
#include "../../../all_diclarations.h"
using sf::Keyboard;

extern bool sliding_8;

Player::Player()
    : Tank(244, 600, 39, 39, oxdan_dragon_c + "/includes/own/includes/battle_city/media/playerSprites.png") {

    buffer_dead_5.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/fire.wav");

    // Create an instance of sf::Sound and set its buffer to the loaded sound buffer

    sound_dead_5.setBuffer(buffer_dead_5);

    sound_dead_5.setVolume(80);

    sf::Sound sound_dead_5;
    sound_dead_5.setBuffer(buffer_dead_5);
    sound_dead_5.setVolume(80);
}

void Player::move(const sf::Int64& time) {

  
        if (Keyboard::isKeyPressed(Keyboard::Left)) {

                mDir = 1;
                mSpeed = 0.11f;

        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {

                mDir = 0;
                mSpeed = 0.11f;

        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {

                mDir = 3;
                mSpeed = 0.11f;

        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {

                mDir = 2;
                mSpeed = 0.11f;

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

void Player::update(const sf::Int64& time, Map& map, const bool& collision) {
    mCollision = collision;
    move(time);

    mSpeed = 0.f;
    mSprite.setPosition(mX, mY);
    animate(time);



    // If the player is not inside the bush, proceed with the regular update logic
    map_interaction(map);

    bullet.update(map, time, mX, mY, mDir);
    if (!bullet.present) {
        if (Keyboard::isKeyPressed(Keyboard::Space)) {

            sound_dead_5.play();

            bullet.timeBeforeShot += time;
            if (bullet.timeBeforeShot > 10.f) {
                
                bullet.present = true;
                bullet.timeBeforeShot = 0.f;
            }
        }
    }
}