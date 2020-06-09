#include "States/GameState.h"

void GameState::initFont()
{
    if (!this->font.loadFromFile("res/fonts/font.otf"))
    {
        std::cout << "couldnt load font" << std::endl;
    }

    if (!this->scoreFont.loadFromFile("res/fonts/scoreFont.ttf"))
    {
        std::cout << "failed to load scorefont" << std::endl;
    }
}

void GameState::initText()
{
    this->points = 0;
    this->scoreText.setFont(this->scoreFont);
    this->scoreText.setCharacterSize(30);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setString("Score: 0");
}

void GameState::initMusic()
{
    if (!this->mainGameMusic.openFromFile("res/bgm/main_game_bgm.ogg"))
    {
        std::cout << "failed to load music" << std::endl;
    }

    if (!this->caveAmbiance.openFromFile("res/sa/ambience.ogg"))
    {
        std::cout << "failed to load ambience" << std::endl;
    }

    this->mainGameMusic.setLoop(true);
    this->mainGameMusic.setVolume(50);
    this->caveAmbiance.setLoop(true);
}

void GameState::initSounds()
{
    if (!this->diamondBuffer.loadFromFile("res/sfx/diamondTake.ogg"))
    {
        std::cout << "failed to load diamond buffer" << std::endl;
    }

    this->diamondSound.setBuffer(this->diamondBuffer);
    this->diamondSound.setVolume(50);
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 800.f, 800.f, "Quitter");

    this->pmenu->addButton("CONTINUE", 800.f, 200.f, "Continuer");
}

void GameState::initTexture()
{
    if (!this->textures["PLAYER_IDLE"].loadFromFile("res/sprites/player/playerIdle.png"))
    {
        std::cout << "failed to load player sprte" << std::endl;
    }

    if (!this->textures["PLAYER_WALK"].loadFromFile("res/sprites/player/playerRun.png"))
    {
        std::cout << "failed to load run sprite" << std::endl;
    }

    if (!this->textures["PLAYER_WALK_LEFT"].loadFromFile("res/sprites/player/playerRunLeft.png"))
    {
        std::cout << "couldnt init left sprite" << std::endl;
    }

    if (!this->textures["BACKGROUND"].loadFromFile("res/sprites/bg/main_game_bg.png"))
    {
        std::cout << "couldnt init bg sprite" << std::endl;
    }

    if (!this->textures["DIAMOND"].loadFromFile("res/sprites/diamonds/diamond.png"))
    {
        std::cout << "couldnt init diamond" << std::endl;
    }

    this->caveSprite.setTexture(this->textures["BACKGROUND"]);
    this->caveSprite.setScale(6, 6);
}

void GameState::initPlayer()
{
    this->player = new Player(830, 500, this->textures["PLAYER_IDLE"]);
}

bool GameState::initShaders()
{
    if (!this->game_shader.loadFromFile("shaders/playerLight.vert", "shaders/playerLight.frag"))
    {
        std::cout << "failed to load main game shaders" << std::endl;
        return this->isShaderLoaded = false;
    }

    return this->isShaderLoaded = true;
}

void GameState::initSystem()
{
    this->tts = new TextTagSystem("res/fonts/font.otf");
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states)
{
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxDiamonds = 5;

    this->initFont();
    this->initText();
    this->initMusic();
    this->initSounds();
    this->initTexture();
    this->initPauseMenu();
    this->initShaders();
    this->initPlayer();
    this->initSystem();
    std::cout << "hello from gamestate" << std::endl;

    this->mainGameMusic.play();
    this->caveAmbiance.play();
}

GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
    delete this->tts;
}

void GameState::endState()
{
    std::cout << "goodbye from gamestate" << std::endl;
    this->mainGameMusic.stop();
    this->caveAmbiance.stop();
    this->states->push(new MainMenuState(this->window, this->states));
}

void GameState::updatePausedInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!this->paused)
            this->pauseState();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        this->endState();
    }
}

void GameState::updateCollision()
{
    for (size_t i = 0; i < this->diamonds.size(); i++)
    {
        if (this->player->getSprite().getGlobalBounds().intersects(this->diamonds[i].getSprite().getGlobalBounds()))
        {
            this->tts->addTextFrag(DEFAULT_TAG, this->player->getPosition().x, this->player->getPosition().y);
            this->points++;
            this->diamondSound.play();
            this->diamonds.erase(this->diamonds.begin() + i);
        }
    }
}

void GameState::updateScore()
{
    this->scoreText.setPosition(this->player->getPosition().x + 30, this->player->getPosition().y - 30);

    this->pointString = std::to_string(this->points);
    this->scoreText.setString("Score: " + this->pointString);
}

void GameState::updateInput(const float& dt)
{
    this->playerAnimation = PLAYER_IDLE;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
        this->endState();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->playerAnimation = PLAYER_RUN;
        this->player->move(1.f, 0.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->playerAnimation = PLAYER_RUN_LEFT;
        this->player->move(-1.f, 0.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->playerAnimation = PLAYER_RUN_LEFT;
        this->player->move(0.f, -1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->playerAnimation = PLAYER_RUN_LEFT;
        this->player->move(0.f, 1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->playerAnimation = PLAYER_RUN;
        this->player->move(0.f, -1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->playerAnimation = PLAYER_RUN;
        this->player->move(0.f, 1.f, dt);
    }
    //UPLEFTRIGHT

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->playerAnimation = PLAYER_RUN_LEFT;
        this->player->move(0.f, -1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->playerAnimation = PLAYER_RUN_LEFT;
        this->player->move(0.f, 1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->playerAnimation = PLAYER_RUN;
        this->player->move(0.f, -1.f, dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->playerAnimation = PLAYER_RUN;
        this->player->move(0.f, 1.f, dt);
    }

    switch (playerAnimation)
    {
    case PLAYER_IDLE:
        this->player->setTexture(this->textures["PLAYER_IDLE"]);
        break;
    case PLAYER_RUN:
        this->player->setTexture(this->textures["PLAYER_WALK"]);
        break;
    case PLAYER_RUN_LEFT:
        this->player->setTexture(this->textures["PLAYER_WALK_LEFT"]);
        break;
    }
}

void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressedMenu("QUIT"))
        this->endState();
    if (this->pmenu->isButtonPressedMenu("CONTINUE"))
        this->unpauseState();
}

void GameState::spawnDiamonds()
{
    if (this->spawnTimer < this->spawnTimerMax)
        this->spawnTimer += 1.f;
    else
    {
        if (this->diamonds.size() < this->maxDiamonds)
        {
            this->diamonds.push_back(Diamond(
                                             (rand() % (this->window->getSize().x - 100)),
                                             (rand() % this->window->getSize().y - 100),
                                             this->textures["DIAMOND"]));

            this->spawnTimer = 0;
        }
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePositions();
    this->updatePausedInput(dt);
    this->player->updateWindowBounds(this->window);

    if (!this->paused)
    {
        this->updateInput(dt);

        game_shader.setUniform("lightPos", sf::Vector2f(this->player->getPosition().x + 100.f, this->player->getPosition().y + 110.F));

        this->player->update(dt);
        this->spawnDiamonds();
        this->updateCollision();
        this->updateScore();
    }
    else
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }

    this->tts->update();
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->clear(sf::Color::Black);

    if (this->isShaderLoaded)
    {
        game_shader.setUniform("hasTexture", true);

        target->draw(this->caveSprite, &game_shader);

        for (auto i : this->diamonds)
        {
            i.render(this->window, &game_shader);
        }

        this->player->render(target, &game_shader);

        target->draw(this->scoreText);
    }

    this->tts->render(*this->window);

    if (this->paused)
    {
        this->pmenu->render(*target);
    }
}
