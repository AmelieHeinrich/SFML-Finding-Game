#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{

}

Player::Player(float pos_x, float pos_y, sf::Texture& texture_sheet)
{
    this->initVariables();

    this->setTexture(texture_sheet);
    this->sprite.setScale(4, 4);
    this->setPosition(pos_x, pos_y);

    this->createMovementComponent(250.f, 10.f, 4.f);
}

Player::~Player()
{
    //dtor
}

void Player::updateWindowBounds(sf::RenderTarget* target)
{
    if (this->sprite.getGlobalBounds().left <= 0)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}
