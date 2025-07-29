 #include <SFML/Window/Event.hpp>
#include "Application_battle_city.h"
#include "Map_battle_city.h"
#include <string>
//#include "level_give.h"
#include "../../../all_diclarations.h"
#include <SFML/Audio.hpp>

//#define APPLICATION_CPP 1

int level_batl_city = 1;

Application::Application()
    : mWindow(sf::VideoMode(720, 672), "Battle City"), gameOver_battle_city(false), gameStarted(false),
    msgStart(90, 330, "Press \'Enter\' to start\n\n       Level " + std::to_string(level_batl_city)), msgOver(250, 300, "Game over"),
    msgLost(260, 350, "You lose"), msgWon(265, 350, "You win"), frags(0)
{

    sf::Image icon;
    icon.loadFromFile(oxdan_dragon_c + "/my_dragon_ico.jpg");

    // Set the window's icon
    mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Clock clock;

    packOfEnemies = new Enemy_1[4]{ Enemy_1(52,31), Enemy_1(147,391), Enemy_1(532,391), Enemy_1(628,31) };

    buffer_start.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/Battle_City_start_game.wav");

    // Create an instance of sf::Sound and set its buffer to the loaded sound buffer
    
    sound_start.setBuffer(buffer_start);

    sound_start.setVolume(80);

    buffer_over.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/Battle_City_over_game.wav");

    // Create an instance of sf::Sound and set its buffer to the loaded sound buffer
    
    sound_over.setBuffer(buffer_over);

    sound_over.setVolume(80);

    sf::Sound soundStart;
    soundStart.setBuffer(buffer_start);
    soundStart.setVolume(80);

    // Create an instance of sf::Sound and set its buffer to the loaded sound buffer
    sf::Sound soundOver;
    soundOver.setBuffer(buffer_over);
    soundOver.setVolume(80);

    while (mWindow.isOpen()) 
    {
        sf::Int64 time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 400;

        process_events();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            gameStarted = true;

        }

        if (gameStarted && !soundStartPlayed)
        {
            // Play the start sound
            soundStart.play();

            // Set the flag to true
            soundStartPlayed = true;
        }
        else if (!gameStarted && soundStartPlayed)
        {
            // Stop the start sound
            soundStart.stop();

            // Set the flag to false
            soundStartPlayed = false;
        }

        if (gameOver_battle_city && !soundOverPlayed)
        {
            // Stop the start sound
            soundStart.stop();

            // Play the game over sound
            soundOver.play();

            // Set the flag to true
            soundOverPlayed = true;
        }
        else if (!gameOver_battle_city && soundOverPlayed)
        {
            // Stop the game over sound
            soundOver.stop();

            // Set the flag to false
            soundOverPlayed = false;
        }

        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (gameStarted == false)
            {
                mWindow.close();

                level_batl_city++;
                if (level_batl_city > 35)
                    level_batl_city = 1;

                process_events();

                Application game;
                //return;
            }
            
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (gameStarted == false)
            {
                mWindow.close();

                level_batl_city--;

                if (level_batl_city <= 0)
                    level_batl_city = 35;

                process_events();

                Application game;
                //return;
            }
        }
        */

        if (gameStarted && !gameOver_battle_city)
            update(time);
        render();
    }
}

void Application::process_events() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                check_start_start();
        }
    }
}

void Application::update(const sf::Int64 &time) {
    for (int i(0); i < 4; ++i)
        if (!packOfEnemies[i].life)
            ++frags;
        else {
            frags = 0;
            break;
        }

    if (frags == 4)
        gameOver_battle_city = true;

    if (!mPlayer.life)
        gameOver_battle_city = true;

    bool collision;
    for (int i(0); i < 4; ++i) {
        collision = mPlayer.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds());
        if (collision)
            break;
    }

    if (mPlayer.life)
        mPlayer.update(time, map, collision);

    for (int i(0); i < 4; ++i) {
        if (packOfEnemies[i].life) {
            packOfEnemies[i].update(time, map, collision);

            if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(mPlayer.mSprite.getGlobalBounds())
                && packOfEnemies[i].bullet.present) {
                mPlayer.collapse();
                packOfEnemies[i].bullet.present = false;
            }

            if (packOfEnemies[i].bullet.mSprite.getGlobalBounds().intersects(mBase.mSprite.getGlobalBounds())
                && packOfEnemies[i].bullet.present) {
                mBase.life = false;
                gameOver_battle_city = true;
            }
            if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(packOfEnemies[i].mSprite.getGlobalBounds())
                && mPlayer.bullet.present) {
                packOfEnemies[i].collapse();
                mPlayer.bullet.present = false;
            }
        }
    }

    if (mPlayer.bullet.mSprite.getGlobalBounds().intersects(mBase.mSprite.getGlobalBounds())
        && mPlayer.bullet.present) {
        mBase.life = false;
        gameOver_battle_city = true;
    }
}

void Application::render() {
    mWindow.clear();
    map.draw(mWindow);
    if (mPlayer.life)
        mWindow.draw(mPlayer.mSprite);
    if (mPlayer.bullet.present) mWindow.draw(mPlayer.bullet.mSprite);

    for (int i(0); i < 4; ++i) {
        if (packOfEnemies[i].bullet.present)
            mWindow.draw(packOfEnemies[i].bullet.mSprite);

        if (packOfEnemies[i].life)
            mWindow.draw(packOfEnemies[i].mSprite);
    }

    if (mBase.life)
        mWindow.draw(mBase.mSprite);

    if (!gameStarted)
        msgStart.print(mWindow);

    if (gameOver_battle_city) {
        msgOver.print(mWindow);
        if (!mBase.life || !mPlayer.life)

            msgLost.print(mWindow);
        else
        {
            
            if (level_batl_city < 35)
            {
                mWindow.close();

                level_batl_city++;

                process_events();

                Application game;
            }

            msgWon.print(mWindow);
        }
    }

    mWindow.display();
}
