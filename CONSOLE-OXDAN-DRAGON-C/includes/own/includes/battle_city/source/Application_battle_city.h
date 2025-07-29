#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Map_battle_city.h"
#include "Player_battle_city.h"
#include "Enemy_battle_city.h"
#include "Base_battle_city.h"
#include "Message_battle_city.h"
#include <SFML/Audio.hpp>

class Application : private sf::NonCopyable {
private:
    
    bool gameOver_battle_city;
    bool gameStarted;

    bool soundStartPlayed;
    bool soundOverPlayed;

    int frags;

    sf::SoundBuffer buffer_over;
    sf::SoundBuffer buffer_start;
    sf::Sound sound_start;
    sf::Sound sound_over;

    sf::RenderWindow mWindow;
    Base mBase;
    Map map;
    Player mPlayer;
    Enemy_1 *packOfEnemies;

    Message msgStart;
    Message msgOver;
    Message msgLost;
    Message msgWon;

public:
    Application();
    void process_events();
    void update(const sf::Int64 &time);
    void render();

};
