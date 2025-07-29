#include "Map_battle_city.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Application_battle_city.h"
#include "../../../all_diclarations.h"
extern int level_batl_city;

Map::Map() : tank(0, 0, 0, 0, "") {
    std::string mapFile;

    if (level_batl_city == 1) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_1.txt";
    }
    else if (level_batl_city == 2) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_2.txt";
    }
    else if (level_batl_city == 3) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_3.txt";
    }
    else if (level_batl_city == 4) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_4.txt";
    }
    else if (level_batl_city == 5) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_5.txt";
    }
    else if (level_batl_city == 6) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_6.txt";
    }
    else if (level_batl_city == 7) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_7.txt";
    }
    else if (level_batl_city == 8) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_8.txt";
    }
    else if (level_batl_city == 9) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_9.txt";
    }
    else if (level_batl_city == 10) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_10.txt";
    }
    else if (level_batl_city == 11) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_11.txt";
    }
    else if (level_batl_city == 12) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_12.txt";
    }
    else if (level_batl_city == 13) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_13.txt";
    }
    else if (level_batl_city == 14) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_14.txt";
    }
    else if (level_batl_city == 15) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_15.txt";
    }
    else if (level_batl_city == 16) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_16.txt";
    }
    else if (level_batl_city == 17) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_17.txt";
    }
    else if (level_batl_city == 18) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_18.txt";
    }
    else if (level_batl_city == 19) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_19.txt";
    }
    else if (level_batl_city == 20) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_20.txt";
    }
    else if (level_batl_city == 21) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_21.txt";
    }
    else if (level_batl_city == 22) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_22.txt";
    }
    else if (level_batl_city == 23) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_23.txt";
    }
    else if (level_batl_city == 24) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_24.txt";
    }
    else if (level_batl_city == 25) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_25.txt";
    }
    else if (level_batl_city == 26) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_26.txt";
    }
    else if (level_batl_city == 27) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_27.txt";
    }
    else if (level_batl_city == 28) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_28.txt";
    }
    else if (level_batl_city == 29) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_29.txt";
    }
    else if (level_batl_city == 30) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_30.txt";
    }
    else if (level_batl_city == 31) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_31.txt";
    }
    else if (level_batl_city == 32) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_32.txt";
    }
    else if (level_batl_city == 33) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_33.txt";
    }
    else if (level_batl_city == 34) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_34.txt";
    }
    else if (level_batl_city == 35) {
        mapFile = oxdan_dragon_c + "/includes/own/includes/battle_city/media/map_35.txt";
    }

    std::ifstream file(mapFile);

    std::string line;
    TileMap = new sf::String[HEIGHT_MAP];

    int idx = 0;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            TileMap[idx] = line;
            idx++;
        }
        file.close();
    }

    mTexture.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/groundSprites.png");
    mTexture.setSmooth(true);
    mSprite.setTexture(mTexture);

    mTexture_bush.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/bush.png");
    mTexture_bush.setSmooth(true);
    mSprite_bush.setTexture(mTexture_bush);

    mTexture_ice.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/ice.png");
    mTexture_ice.setSmooth(true);
    mSprite_ice.setTexture(mTexture_ice);

    mTexture_water.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/water.png");
    mTexture_water.setSmooth(true);
    mSprite_water.setTexture(mTexture_water);

}

void Map::break_wall(const int& i, const int& j) {
    TileMap[i][j] = ' ';
}

void Map::draw(sf::RenderWindow& window) {
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            switch (TileMap[i][j]) {
            case ' ':
                mSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '.':
                mSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '0':
                mSprite.setTextureRect(sf::IntRect(72, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '#':
                mSprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '1':
                mSprite.setTextureRect(sf::IntRect(24, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '@':
                mSprite.setTextureRect(sf::IntRect(48, 0, 24, 24));
                mSprite.setPosition(j * 24, i * 24);
                window.draw(mSprite);
                break;
            case '%':
                if (tank.getX() >= j * 24 && tank.getX() < (j + 1) * 24 && tank.getY() >= i * 24 && tank.getY() < (i + 1) * 24) {
                    //mSprite_bush.setTextureRect(sf::IntRect(0, 0, 24, 24)); // Replace with desired texture rectangle for tank inside '3'
                    mSprite_bush.setTextureRect(sf::IntRect(0, 0, 48, 53));
                    mSprite_bush.setPosition(j * 24, i * 24);
                    window.draw(mSprite_bush);
                    break;
                }
                else {
                    mSprite_bush.setTextureRect(sf::IntRect(0, 0, 48, 53));
                    mSprite_bush.setPosition(j * 24, i * 24);
                    window.draw(mSprite_bush);
                    break;
                }
                break;
            case '~':
                mSprite_water.setTextureRect(sf::IntRect(0, 0, 48, 53));
                mSprite_water.setPosition(j * 24, i * 24);
                window.draw(mSprite_water);
                break;
            case '-':
                mSprite_ice.setTextureRect(sf::IntRect(0, 0, 48, 53));
                mSprite_ice.setPosition(j * 24, i * 24);
                window.draw(mSprite_ice);
                break;
            }


        }
    }
}
