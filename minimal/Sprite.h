#pragma once
#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height);
	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;

	// VBO! 
	GLuint _vboID; // 32bit guaranteed 

};

