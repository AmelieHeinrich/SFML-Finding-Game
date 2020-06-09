#include "States/State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
    this->window = window;
    this->states = states;
    this->quit = false;
    this->paused = false;
}

State::~State()
{
    //dtor
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}
