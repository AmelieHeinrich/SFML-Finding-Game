#include "CreditsState.h"

void CreditsState::initFonts()
{
    if (!this->font.loadFromFile("res/fonts/font.otf"))
    {
        std::cout << "couldnt load font" << std::endl;
    }

    this->creditsText.setFont(this->font);
    this->creditsText.setFillColor(sf::Color::White);
    this->creditsText.setCharacterSize(40);
    this->creditsText.setString("Ce jeu a été crée à l'occasion du spectacle de fin d'année d'EGG.\nTout a été programmé en C++ avec la librairie multimédia SFML.\nLe projet pris 2 semaines a réaliser, et il possède en tout un total de 1367 lignes de code.\n\nJe suis très heureux d'avoir réalisé ce projet, et j'espère pouvoir en faire d'autre dans le futur c:\n\nMilo");
    this->creditsText.setPosition(300, 200);
}

void CreditsState::initSound()
{
    if (!this->hoverBuffer.loadFromFile("res/sfx/buttonHover.ogg"))
    {
        std::cout << "failed to load hover ogg" << std::endl;
    }

    this->hoverSound.setBuffer(this->hoverBuffer);
}

void CreditsState::initMusic()
{
    if (!this->creditsMusic.openFromFile("res/bgm/credits_bgm.ogg"))
    {
        std::cout << "failed to load 7pm" << std::endl;
    }

    this->creditsMusic.setVolume(30);
    this->creditsMusic.play();
}

void CreditsState::initButtons()
{
    this->go_back = new Button(50, 50, 300, 100,
                               &this->font, "Retour",
                                sf::Color(70, 70, 70, 200),
                                sf::Color(150, 150, 150, 200),
                                sf::Color(20, 20, 20, 200));
}

void CreditsState::initGraphics()
{
    if (!this->screen1Tex.loadFromFile("res/sprites/bg/screen1.png"))
    {
        std::cout << "failed to load screen" << std::endl;
    }

    if (!this->screen2Tex.loadFromFile("res/sprites/bg/screen2.png"))
    {
        std::cout << "failed to load second screen" << std::endl;
    }

    if (!this->logoTex.loadFromFile("res/sprites/logo/mixel.png"))
    {
        std::cout << "failed to load mixel" << std::endl;
    }

    if (!this->sfmlTex.loadFromFile("res/sprites/logo/sfml.png"))
    {
        std::cout << "failed to load sfml" << std::endl;
    }

    if (!this->cppTex.loadFromFile("res/sprites/logo/cpp.png"))
    {
        std::cout << "failed to load cpp" << std::endl;
    }

    if (!this->playerTex.loadFromFile("res/sprites/player/playerIdle.png"))
    {
        std::cout << "failed to load player" << std::endl;
    }

    this->screen1.setTexture(this->screen1Tex);
    this->screen2.setTexture(this->screen2Tex);
    this->logo.setTexture(this->logoTex);
    this->sfmlSprite.setTexture(this->sfmlTex);
    this->cppSprite.setTexture(this->cppTex);
    this->player.setTexture(this->playerTex);

    this->screen1.setScale(0.5, 0.5);
    this->screen2.setScale(0.4, 0.4);
    this->logo.setScale(0.9, 0.9);
    this->sfmlSprite.setScale(0.1, 0.1);
    this->cppSprite.setScale(0.1, 0.1);
    this->player.setScale(5, 5);

    this->screen1.setPosition(0, 800);
    this->screen2.setPosition(700, 600);
    this->logo.setPosition(730, 50);
    this->sfmlSprite.setPosition(1700, 400);
    this->cppSprite.setPosition(1700, 200);
    this->player.setPosition(1300, 800);
}

CreditsState::CreditsState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    std::cout << "hello from credits state" << std::endl;

    this->initFonts();
    this->initSound();
    this->initMusic();
    this->initButtons();
    this->initGraphics();
}

CreditsState::~CreditsState()
{
    delete this->go_back;
}

bool CreditsState::getHover(Button* button)
{
    if (button->isHovered())
        return true;

    return false;
}


void CreditsState::endState()
{
    std::cout << "Goodbye from credits state" << std::endl;
    this->creditsMusic.stop();
    this->states->push(new MainMenuState(this->window, this->states));
}

void CreditsState::updateInput(const float& dt)
{

}

void CreditsState::updateButtonPress()
{
    if (this->go_back->isPressed())
    {
        this->endState();
    }

    if (getHover(go_back))
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

void CreditsState::update(const float& dt)
{
    this->updateInput(dt);
    this->updateMousePositions();
    this->go_back->update(this->mousePosView);
    this->updateButtonPress();
}

void CreditsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->clear(sf::Color::Black);

    target->draw(this->screen1);
    target->draw(this->screen2);
    target->draw(this->logo);
    target->draw(this->sfmlSprite);
    target->draw(this->cppSprite);
    target->draw(this->player);

    target->draw(this->creditsText);

    this->go_back->render(target);
}
