#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "CreditsState.h"
#include "UI/Button.h"

class MainMenuState : public State
{
private:
    sf::Font font;

    sf::Music mainMenuMusic;

    sf::SoundBuffer hoverBuffer;
    sf::Sound hoverSound;

    sf::Texture bgTexture;
    sf::Texture torchTexture;
    sf::Texture logoTexture;
    sf::Texture incTexture;

    sf::Sprite bgSprite;
    sf::Sprite torchSprite, torchSprite2;
    sf::Sprite logoSprite;
    sf::Sprite incSprite;

    sf::Shader core_shader;
    bool shaderInit;

    Button *gamestate_btn;
    Button *credits_btn;
    Button *quit_btn;

    bool isHover;

    void initFonts();
    void initMusic();
    void initSounds();
    void initGraphics();
    bool initShaders();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~MainMenuState();

    bool getHover(Button* button);

    void endState();
    void updateInput(const float& dt);
    void updateButtonPress();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // MAINMENUSTATE_H
