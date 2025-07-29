#include "Tank_battle_city.h"
#include "Map_battle_city.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include "../../../all_diclarations.h"
using sf::Keyboard;

bool sliding_8 = false;

Tank::Tank(const float& x, const float& y, const float& width, const float& height, const sf::String& file)
    : life(true), mX(x), mY(y), mDx(0.f), mDy(0.f), mFile(file), mDir(0), mCollision(false),
    mCurrentFrame(0.f), mSpeed(0.f), mWidth(width), mHeight(height),
    bullet(x, y) {

    mTexture.loadFromFile(mFile);
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(78, 39, mWidth, mHeight));
    mSprite.setPosition(x, y);

    if (!buffer_explosion.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/explosion.wav")) {
        // Handle error: Unable to load sound file
    }

    sound_explosion.setBuffer(buffer_explosion);

}

void Tank::animate(const sf::Int64& time) {
    mCurrentFrame += 0.005f * time;
    if (mCurrentFrame >= 2)
        mCurrentFrame -= 2;

    if (mDx > 0.f)
        mSprite.setTextureRect(sf::IntRect(0 + 39 * (int)mCurrentFrame, 0, 39, 39));
    if (mDx < 0.f)
        mSprite.setTextureRect(sf::IntRect(78 + 39 * (int)mCurrentFrame, 0, 39, 39));
    if (mDy > 0.0f)
        mSprite.setTextureRect(sf::IntRect(0 + 39 * (int)mCurrentFrame, 39, 39, 39));
    if (mDy < 0.0f)
        mSprite.setTextureRect(sf::IntRect(78 + 39 * (int)mCurrentFrame, 39, 39, 39));
}

void Tank::collapse() {
    life = false;
    sound_explosion.play();
    bullet.present = false;
    mSprite.setPosition(0, 0);
}

float Tank::getX() const {
    return mX;
}

float Tank::getY() const {
    return mY;
}

void Tank::move(const sf::Int64& time) {
    mX += mDx * mSpeed * time;
    mY += mDy * mSpeed * time;
}

void Tank::map_interaction(Map& map) {
    bool isTankInsideTile3 = false;
    for (int i = mY / 24; i < (mY + mHeight) / 24; ++i) {
        for (int j = mX / 24; j < (mX + mWidth) / 24; ++j) {
            char tile = map.get_tile(i, j);

            if (tile >= '0' && tile <= '@') {
                sliding_8 = false;
                if (mDy > 0.f) {
                    mY = i * 24 - mHeight;
                }
                if (mDy < 0.f) {
                    mY = (float)i * 24 + 24;
                }
                if (mDx > 0.f) {
                    mX = j * 24 - mWidth;
                }
                if (mDx < 0.f) {
                    mX = (float)j * 24 + 24;
                }
            }

            if (tile == '~') {
                sliding_8 = false;
                if (mDy > 0.f) {
                    mY -= 0.3f;
                }
                if (mDy < 0.f) {
                    mY += 0.3f;
                }
                if (mDx > 0.f) {
                    mX -= 0.3f;
                }
                if (mDx < 0.f) {
                    mX += 0.3f;
                }
            }

            

            if (tile == '-') 
            {
                mSpeed = 0.15f;
                sliding_8 = true;
                if (sliding_8 == true && tile == '-')
                {
                    if (Keyboard::isKeyPressed(Keyboard::Left)) {

                        continue;
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Right)) {

                        continue;
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Up)) {

                        continue;
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        
                        continue;

                    }
                }

            }
            if (tile != '-')
            {
                sliding_8 = false;
            }

            
        }

        if (isTankInsideTile3)
            continue;
       
    }

    mSprite.setColor(isTankInsideTile3 ? sf::Color::Transparent : sf::Color::White);
}


void Tank::tank_interaction() {
    if (mDy > 0.f)
        mY -= 0.3f;

    if (mDy < 0.f)
        mY += 0.3f;

    if (mDx > 0.f)
        mX -= 0.3f;

    if (mDx < 0.f)
        mX += 0.3f;
}
