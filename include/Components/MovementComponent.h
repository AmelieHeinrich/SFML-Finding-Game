#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

class MovementComponent
{
private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    const sf::Vector2f& getVelocity() const;

    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);
};

#endif // MOVEMENTCOMPONENT_H
