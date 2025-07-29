//#include <SFML/System/String.hpp>
#include "Message_battle_city.h"
#include "../../../all_diclarations.h"

Message::Message(const float &x, const float &y, const sf::String &str)
    : mX(x), mY(y) {
    
    mFont.loadFromFile(oxdan_dragon_c + "/includes/own/includes/battle_city/media/PressStart2P.ttf");
    mStr.setFont(mFont);
    mStr.setString(str);
    mStr.setPosition(mX, mY);
    mStr.setCharacterSize(25);
}
