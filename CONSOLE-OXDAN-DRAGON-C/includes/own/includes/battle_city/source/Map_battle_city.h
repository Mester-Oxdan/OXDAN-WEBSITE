#pragma once
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Tank_battle_city.h"

class Map : private sf::NonCopyable {
private:
    static const int HEIGHT_MAP = 28;
    static const int WIDTH_MAP = 30;

    sf::String* TileMap;
    sf::Texture mTexture;
    sf::Sprite mSprite;

    sf::Texture mTexture_bush;
    sf::Texture mTexture_water;
    sf::Texture mTexture_ice;
    sf::Sprite mSprite_bush;
    sf::Sprite mSprite_water;
    sf::Sprite mSprite_ice;

public:
    Map();

    void break_wall(const int& i, const int& j);
    const char get_tile(const int& i, const int& j) { return TileMap[i][j]; }
    void draw(sf::RenderWindow& window);
    Tank tank;
};
