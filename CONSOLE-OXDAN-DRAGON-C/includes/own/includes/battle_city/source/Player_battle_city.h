#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "Tank_battle_city.h"
#include <SFML/Audio.hpp>

class Player : public Tank {
private:
    
    sf::SoundBuffer buffer_dead_5;
    sf::Sound sound_dead_5;

public:
    Player();

    void move(const sf::Int64& time);
    void update(const sf::Int64& time, Map& map, const bool& collision);
};
