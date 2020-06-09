#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    MovementComponent* movementComponent;

public:
    Entity();
    virtual ~Entity();

    void setTexture(sf::Texture& texture);
    void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float& dt);

    sf::Vector2f getOrigin() { return this->sprite.getOrigin(); }
    sf::Vector2f getPosition() { return this->sprite.getPosition(); }

    const sf::Sprite getSprite() const { return this->sprite; }

    virtual void updateWindowBounds(sf::RenderTarget* target) = 0;
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target, sf::Shader* shader);

};

#endif // ENTITY_H
