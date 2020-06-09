#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player : public Entity
{
private:
    void initVariables();
    void initComponents();

public:
    Player(float pos_x, float pos_y, sf::Texture& texture_sheet);
    virtual ~Player();

    void updateWindowBounds(sf::RenderTarget* target);
};

#endif // PLAYER_H
