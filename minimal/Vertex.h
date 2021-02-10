#pragma once

#include "gl/glew.h"

struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex // composition
{
	Position position;
	//float position[2];//4 byte

	Color color;
	//GLubyte color[4];
};