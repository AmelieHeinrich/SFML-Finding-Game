#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include "MainMenuState.h"

class CreditsState : public State
{
private:
    sf::Texture screen1Tex;
    sf::Texture screen2Tex;
    sf::Texture logoTex;
    sf::Texture sfmlTex;
    sf::Texture cppTex;
    sf::Texture playerTex;

    sf::Sprite screen1;
    sf::Sprite screen2;
    sf::Sprite logo;
    sf::Sprite sfmlSprite;
    sf::Sprite cppSprite;
    sf::Sprite player;

    sf::Font font;
    sf::Text creditsText;

    sf::SoundBuffer hoverBuffer;
    sf::Sound hoverSound;

    sf::Music creditsMusic;

    Button *go_back;

    bool isHover;

    void initFonts();
    void initSound();
    void initMusic();
    void initButtons();
    void initGraphics();

public:
    CreditsState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~CreditsState();

    bool getHover(Button* button);

    void endState();
    void updateInput(const float& dt);
    void updateButtonPress();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // CREDITSSTATE_H
