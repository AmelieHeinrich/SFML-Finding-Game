#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) : sprite(sprite), textureSheet(texture_sheet)
{
    //ctor
}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }
}

void AnimationComponent::addAnimation(const char* key, float animation_timer, int start_x, int start_y, int end_x, int end_y, int width, int height)
{
    this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer, start_x, start_y, end_x, end_y, width, height);
}

void AnimationComponent::play(const char* key, const float& dt)
{
    this->animations[key]->play(dt);
}
