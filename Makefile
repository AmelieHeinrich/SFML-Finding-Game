##
## EPITECH PROJECT, 2023
## SFML-Finding-Game
## File description:
## Makefile
##

NAME = Game
CC = g++
SOURCES = src/main.cpp \
		  src/Game.cpp \
		  src/Components/AnimationComponent.cpp \
		  src/Components/MovementComponent.cpp \
		  src/Entity/Diamond.cpp \
		  src/Entity/Entity.cpp \
		  src/Entity/Player.cpp \
		  src/States/CreditsState.cpp \
		  src/States/GameState.cpp \
		  src/States/MainMenuState.cpp \
		  src/States/State.cpp \
		  src/UI/Button.cpp \
		  src/UI/PauseMenu.cpp \
		  src/UI/TextTagSystem.cpp
LINK_PATH = -LSFML-2.5.1/lib
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCLUDE_PATH = -ISFML-2.5.1/include -Iinclude -Iinclude/Components -Iinclude/Entity -Iinclude/States -Iinclude/UI

all: $(NAME)

$(NAME):
	$(CC) $(SOURCES) $(LINK_PATH) $(LIBS) $(INCLUDE_PATH) -o bin/$(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all, $(NAME), clean, re
