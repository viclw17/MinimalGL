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

struct UV {
	float u;
	float v;
};

struct Vertex // composition
{
	Position position;
	//float position[2];//4 byte

	Color color;
	//GLubyte color[4];

	UV uv;


	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};