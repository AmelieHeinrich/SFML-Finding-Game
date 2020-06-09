#include "States/MainMenuState.h"

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("res/fonts/font.otf"))
    {
        std::cout << "couldnt load font" << std::endl;
    }
}

void MainMenuState::initMusic()
{
    if (!this->mainMenuMusic.openFromFile("res/bgm/main_menu_bgm.ogg"))
    {
        std::cout << "failed to load main menu music" << std::endl;
    }

    this->mainMenuMusic.setLoop(true);
}

void MainMenuState::initSounds()
{
    if (!this->hoverBuffer.loadFromFile("res/sfx/buttonHover.ogg"))
    {
        std::cout << "failed to load hover ogg" << std::endl;
    }

    this->hoverSound.setBuffer(this->hoverBuffer);
}

void MainMenuState::initGraphics()
{
    if (!this->bgTexture.loadFromFile(("res/sprites/bg/background.jpg")))
    {
        std::cout << "couldnt load font" << std::endl;
    }

    if (!this->torchTexture.loadFromFile("res/sprites/objects/torch.png"))
    {
        std::cout << "couldnt load torch" << std::endl;
    }

    if (!this->logoTexture.loadFromFile("res/sprites/logo/logo.png"))
    {
        std::cout << "couldnt load logo" << std::endl;
    }

    if (!this->incTexture.loadFromFile("res/sprites/logo/mixel.png"))
    {
        std::cout << "failed to load mixel" << std::endl;
    }

    this->bgSprite.setTexture(this->bgTexture);
    this->torchSprite.setTexture(this->torchTexture);
    this->torchSprite2.setTexture(this->torchTexture);
    this->logoSprite.setTexture(this->logoTexture);
    this->incSprite.setTexture(this->incTexture);

    this->torchSprite.setScale(0.5, 0.5);
    this->torchSprite2.setScale(0.5, 0.5);
    this->bgSprite.setScale(2.f, 2.f);
    this->incSprite.setScale(0.5, 0.5);

    this->torchSprite.setPosition(600, 150);
    this->torchSprite2.setPosition(1200, 150);
    this->logoSprite.setPosition(730, 50);
    this->incSprite.setPosition(0, 1030);
}

bool MainMenuState::initShaders()
{
    if (!this->core_shader.loadFromFile("shaders/light1.vert", "shaders/light1.frag"))
    {
        std::cout << "error loading shaders" << std::endl;
        return this->shaderInit = false;
    }

    return this->shaderInit = true;
}

void MainMenuState::initButtons()
{
    this->gamestate_btn = new Button(800, 300, 300, 100,
                                    &this->font, "Nouvelle partie",
                                    sf::Color(70, 70, 70, 200),
                                    sf::Color(150, 150, 150, 200),
                                    sf::Color(20, 20, 20, 200));

    this->credits_btn = new Button(800, 500, 300, 100,
                                    &this->font, "Credits",
                                    sf::Color(70, 70, 70, 200),
                                    sf::Color(150, 150, 150, 200),
                                    sf::Color(20, 20, 20, 200));

    this->quit_btn = new Button(800, 700, 300, 100,
                                    &this->font, "Quitter",
                                    sf::Color(70, 70, 70, 200),
                                    sf::Color(150, 150, 150, 200),
                                    sf::Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    std::cout << "hello from main menu state" << std::endl;

    this->isHover = false;

    this->initFonts();
    this->initMusic();
    this->initSounds();
    this->initGraphics();
    this->initShaders();
    this->initButtons();

    this->mainMenuMusic.play();
}

MainMenuState::~MainMenuState()
{
    delete this->gamestate_btn;
}

bool MainMenuState::getHover(Button* button)
{
    if (button->isHovered())
        return true;

    return false;
}

void MainMenuState::endState()
{
    std::cout << "goodbye from main menu state" << std::endl;
    this->mainMenuMusic.stop();
    this->states->push(new GameState(this->window, this->states));
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtonPress()
{
    if (gamestate_btn->isPressed())
    {
        this->endState();
    }

    if (credits_btn->isPressed())
    {
        this->mainMenuMusic.stop();
        this->states->push(new CreditsState(this->window, this->states));
    }

    if (quit_btn->isPressed())
    {
        this->window->close();
    }

    if (getHover(gamestate_btn))
    {
        if (!this->isHover)
        {
            this->isHover = true;
            this->hoverSound.play();
        }
    }
    else if (getHover(credits_btn))
    {
        if (!this->isHover)
        {
            this->isHover = true;
            this->hoverSound.play();
        }
    }
    else if(getHover(quit_btn))
    {
        if (!this->isHover)
        {
            this->isHover = true;
            this->hoverSound.play();
        }
    }
    else
    {
        this->isHover = false;
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateInput(dt);
    this->updateMousePositions();
    this->gamestate_btn->update(this->mousePosView);
    this->credits_btn->update(this->mousePosView);
    this->quit_btn->update(this->mousePosView);
    this->updateButtonPress();
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->clear(sf::Color::Black);

    if (shaderInit)
    {
        core_shader.setUniform("hasTexture", true);
        core_shader.setUniform("lightPos", sf::Vector2f(670, 300));
        core_shader.setUniform("lightPos2", sf::Vector2f(1270, 300));

        target->draw(this->bgSprite, &core_shader);
        target->draw(this->torchSprite, &core_shader);
        target->draw(this->torchSprite2, &core_shader);
        target->draw(this->logoSprite, &core_shader);
        target->draw(this->incSprite);
    }
    else
    {
        target->draw(this->bgSprite);
        target->draw(this->torchSprite);
        target->draw(this->torchSprite2);
    }

    this->gamestate_btn->render(target);
    this->credits_btn->render(target);
    this->quit_btn->render(target);
}


