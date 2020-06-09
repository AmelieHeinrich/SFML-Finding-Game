#include "Button.h"

Button::Button(float x, float y, float width, float height,
           sf::Font* font, std::string text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    this->buttonState = BTN_IDLE;

    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(x, y);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(30);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 5.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
    //dtor
}

bool Button::isPressed()
{
    if (this->buttonState == BTN_ACTIVE)
        return true;

    return false;
}

bool Button::isHovered()
{
    if (this->buttonState == BTN_HOVER)
        return true;

    return false;
}

void Button::update(const sf::Vector2f& mousePos)
{
    this->buttonState = BTN_IDLE;

    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}
