#ifndef DIAMOND_H
#define DIAMOND_H

#include "Entity.h"


class Diamond
{
private:
    sf::Texture diamondTexture;
    sf::Sprite diamondSprite;

    void initGraphic();

public:
    Diamond(float pos_x, float pos_y, sf::Texture& texture_sheet);
    virtual ~Diamond();

    void render(sf::RenderTarget* target, sf::Shader* shader);
    sf::Sprite getSprite();
    sf::FloatRect getGlobalBounds();
    const sf::Vector2f getPosition();
};

#endif // DIAMOND_H
