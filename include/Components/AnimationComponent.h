#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class AnimationComponent
{
private:
    class Animation
    {
    public:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;
        float timer;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animation_timer, int start_x, int start_y, int end_x, int end_y, int width, int height) : sprite(sprite), textureSheet(textureSheet), animationTimer(animation_timer), width(width), height(height)
        {
            this->startRect = sf::IntRect(start_x * width, start_y * height, width, height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect(end_x * width, end_y * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }

        void play(const float& dt)
        {
            this->timer = 10.f * dt;
            if (this->timer >= this->animationTimer)
            {
                this->timer = 0.f;

                if (this->currentRect != this->endRect)
                {
                    this->currentRect.left += this->width;
                }
                else
                {
                    this->currentRect.left = this->startRect.left;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
        }

        void reset()
        {
            this->timer = 0.f;
            this->currentRect = this->startRect;
        }
    };

    sf::Sprite& sprite;
    sf::Texture& textureSheet;

    std::map<const char*, Animation*> animations;

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    void addAnimation(const char* key, float animation_timer, int start_x, int start_y, int end_x, int end_y, int width, int height);

    void play(const char* key, const float& dt);

};

#endif // ANIMATIONCOMPONENT_H
