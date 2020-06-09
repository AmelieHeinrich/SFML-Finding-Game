#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "Button.h"

class PauseMenu
{
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button*> buttons;

public:
    PauseMenu(sf::RenderWindow& window, sf::Font& font);
    virtual ~PauseMenu();

    std::map<std::string, Button*>& getButtons();

    bool isButtonPressedMenu(std::string key);
    void addButton(const std::string key, float x, float y, const std::string text);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
};

#endif // PAUSEMENU_H
