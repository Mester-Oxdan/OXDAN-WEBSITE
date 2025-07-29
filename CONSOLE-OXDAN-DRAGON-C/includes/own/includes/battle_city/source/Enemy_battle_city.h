#pragma once
#include "Tank_battle_city.h"
#include <SFML/Audio.hpp>

class Enemy_1 : public Tank {
private:
    float timeBeforeMoving;
    float timeBeforeShot;
    sf::SoundBuffer buffer_dead_4;
    sf::Sound sound_dead_4;

public:
    Enemy_1(const float &x, const float &y);
    Enemy_1(const Enemy_1 &copy) : Enemy_1(copy.mX, copy.mY){}

    void move(const sf::Int64 &time);
    void shoot(const float &time);
    void update(const sf::Int64 &time, Map &map, const bool &collision);
};
