#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Bullet_battle_city.h"
#include <SFML/Audio.hpp>

class Map;

class Tank : private sf::NonCopyable {
protected:
    float mX, mY, mWidth, mHeight, mDx, mDy, mSpeed;
    int mDir;
    float mCurrentFrame;
    bool mCollision;

    sf::String mFile;
    sf::Texture mTexture;

private:

    sf::SoundBuffer buffer_explosion;
    sf::Sound sound_explosion;
    

public:
    bool life;
    Bullet bullet;
    sf::Sprite mSprite;

    explicit Tank(const float& x, const float& y, const float& width, const float& height, const sf::String& file);

    float getX() const;
    float getY() const;

    void animate(const sf::Int64& time);
    void collapse();
    virtual void move(const sf::Int64& time);
    void map_interaction(Map& map);
    void tank_interaction();
};
