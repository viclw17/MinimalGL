#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystem();
	void initShaders();
	void processInput();
	void gameLoop();
	void drawGame();

	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	Sprite _sprite;
	GLSLProgram _colorProgram;

	float _time;
};


