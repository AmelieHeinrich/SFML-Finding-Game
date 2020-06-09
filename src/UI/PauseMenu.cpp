#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : font(font)
{
    this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
    this->background.setFillColor(sf::Color(20, 20, 20, 150));

    this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, static_cast<float>(window.getSize().y)));
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0);

    //Init font
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(850.f, 20.f);
}

PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

bool PauseMenu::isButtonPressedMenu(std::string key)
{
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(std::string key, float x, float y, const std::string text)
{
    this->buttons[key] = new Button(x, y, 300, 100,
                                    &this->font, text,
                                    sf::Color(70, 70, 70, 200),
                                    sf::Color(150, 150, 150, 200),
                                    sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
    for (auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget& target)
{
    target.draw(this->background);
    target.draw(this->container);

    for (auto &i : this->buttons)
    {
        i.second->render(&target);
    }

    target.draw(this->menuText);
}
