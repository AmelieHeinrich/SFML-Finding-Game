#include "Game.h"

void Game::initWindow()
{
    this->gameWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Game", sf::Style::Fullscreen);
    this->gameWindow->setFramerateLimit(144);
    std::cout << "window init" << std::endl;
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->gameWindow, &this->states));
}

void Game::initFps()
{
    if (!this->font.loadFromFile("res/fonts/font.otf"))
    {
        std::cout << "error loading font!" << std::endl;
    }

    this->fpsText.setFont(this->font);
    this->fpsText.setPosition(0, 0);
    this->fpsText.setCharacterSize(40);
    this->fpsText.setFillColor(sf::Color::Yellow);
}

Game::Game()
{
    this->initWindow();
    this->initStates();
    this->initFps();
}

Game::~Game()
{
    delete this->gameWindow;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }

    std::cout << "Goodbye from game window" << std::endl;
}

void Game::endApplication()
{
    std::cout << "ending app" << std::endl;
}

void Game::run()
{
    while (this->gameWindow->isOpen())
    {
        this->update();
        this->render();
    }
}

void Game::updateDt()
{
    this->dt = this->dtClock.getElapsedTime().asSeconds();
    this->fps = this->dtClock.restart();
    this->framerate = 1 / (fps.asMilliseconds() * 0.001);
}

void Game::updateSFML()
{
    while (this->gameWindow->pollEvent(this->gameEvent))
        if (this->gameEvent.type == sf::Event::Closed)
            this->gameWindow->close();
}

void Game::update()
{
    this->updateDt();
    this->updateSFML();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        this->fpsString = std::to_string(static_cast<int>(this->framerate));
        this->fpsText.setString(this->fpsString);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }

    else
    {
        this->endApplication();
        this->gameWindow->close();
    }
}

void Game::render()
{
    this->gameWindow->clear();

    if (!this->states.empty())
    {
        this->states.top()->render(this->gameWindow);
        this->gameWindow->draw(this->fpsText);
    }


    this->gameWindow->display();
}



