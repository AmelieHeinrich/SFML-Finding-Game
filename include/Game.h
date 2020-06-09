#ifndef GAME_H
#define GAME_H

#include "States/GameState.h"
#include "States/MainMenuState.h"
#include "States/CreditsState.h"

class Game
{
    private:
        sf::RenderWindow* gameWindow;
        sf::Event gameEvent;

        sf::Clock dtClock;
        float dt;
        float framerate;
        sf::Time fps;

        std::string fpsString;

        std::stack<State*> states;

        sf::Font font;
        sf::Text fpsText;

        void initWindow();
        void initStates();
        void initFps();

    public:
        Game();
        virtual ~Game();

        void endApplication();

        void run();

        void updateDt();
        void updateSFML();
        void update();

        void render();
};

#endif // GAME_H
