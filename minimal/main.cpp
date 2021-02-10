//#include <Windows.h>
#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "MainGame.h"


int main(int argc, char** argv) { // argument count, argument v, an array of c strings
	MainGame mainGame;
	mainGame.run();
	return 0;
}