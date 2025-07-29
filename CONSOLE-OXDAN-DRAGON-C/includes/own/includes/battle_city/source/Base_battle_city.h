#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

class Base : private sf::NonCopyable {
private:
    sf::Texture mTexture;

public:
    sf::Sprite mSprite;
    bool life;

    Base();
};
