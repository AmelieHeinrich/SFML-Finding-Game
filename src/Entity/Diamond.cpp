#include "Diamond.h"

void Diamond::initGraphic()
{
    if (!this->diamondTexture.loadFromFile("res/sprites/diamonds/diamond.png"))
    {
        std::cout << "failed to load diamond" << std::endl;
    }

    this->diamondSprite.setScale(0.12, 0.12);
}

Diamond::Diamond(float pos_x, float pos_y, sf::Texture& texture_sheet)
{
    this->initGraphic();
    this->diamondSprite.setTexture(texture_sheet);
    this->diamondSprite.setPosition(pos_x, pos_y);
}

Diamond::~Diamond()
{

}

void Diamond::render(sf::RenderTarget* target, sf::Shader* shader)
{
    target->draw(this->diamondSprite, shader);
}

sf::Sprite Diamond::getSprite()
{
    return this->diamondSprite;
}

sf::FloatRect Diamond::getGlobalBounds()
{
    return this->diamondSprite.getGlobalBounds();
}

const sf::Vector2f Diamond::getPosition()
{
    return this->diamondSprite.getPosition();
}
