#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "States/State.h"
#include "States/MainMenuState.h"
#include "Player.h"
#include "Diamond.h"
#include "PauseMenu.h"
#include "TextTagSystem.h"

enum playerState { PLAYER_IDLE = 0, PLAYER_RUN, PLAYER_RUN_LEFT };

class GameState : public State
{
private:
    short unsigned playerAnimation;

    sf::Font font;
    sf::Font scoreFont;

    sf::Text scoreText;

    sf::Sprite caveSprite;

    sf::Shader game_shader;
    bool isShaderLoaded;

    sf::Music mainGameMusic;
    sf::Music caveAmbiance;

    sf::SoundBuffer diamondBuffer;
    sf::Sound diamondSound;

    PauseMenu* pmenu;

    Player* player;

    std::vector<Diamond> diamonds;
    float spawnTimer;
    float spawnTimerMax;
    int maxDiamonds;

    int points;

    TextTagSystem* tts;

    std::string pointString;

    void initFont();
    void initText();
    void initMusic();
    void initSounds();
    void initPauseMenu();
    void initTexture();
    bool initShaders();
    void initPlayer();
    void initSystem();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();

    void endState();

    void updatePausedInput(const float& dt);
    void updateCollision();
    void updateScore();
    void updateInput(const float& dt);
    void updatePauseMenuButtons();

    void spawnDiamonds();

    void update(const float& dt);

    void render(sf::RenderTarget* target = nullptr);
};

#endif // GAMESTATE_H
