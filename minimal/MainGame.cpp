#include "MainGame.h"
#include <iostream>
#include "Errors.h"
#include "imageLoader.h"


MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 512;//1024;
	_screenHeight = 512;// 768;
	_gameState = GameState::PLAY;
	_time = 0.0f;
}

MainGame::~MainGame()
{

}

void MainGame::run()
{
	initSystem();
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_sprite.init(-1.0f,-1.0f,2.0f,2.0);
	_playerTexture = imageLoader::loadPNG("Textures/fine.png");

	gameLoop();
}

void MainGame::initSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("MinimalGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		fatalError("SDL window could not be created!");
	}

	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	if (glContex == nullptr) {
		fatalError("SDL_GL context cant be created!");
	}

	//glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW cant be initialized!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // double buffer, smooth
	glClearColor(0,0,1,1);

	initShaders();
}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) // take a ptr
	{
		// we have an event
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;

		default:
			break;
		}
	}
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		drawGame();
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// raw draw
	//glEnableClientState(GL_COLOR_ARRAY);
	//glBegin(GL_TRIANGLES);
	//glVertex2f(0, 0); //NDC
	//glVertex2f(0,500);
	//glVertex2f(500, 500);
	//glColor3f(1, 0, 0);
	//glEnd();


	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0); // multi tex
	glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);


	_sprite.draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();


	SDL_GL_SwapWindow(_window);
}
