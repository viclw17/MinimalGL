#include "Sprite.h"
#include "Vertex.h"
#include <cstddef> // offsetof

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	// free buffer
	if (_vboID != 0)
		glDeleteBuffers(1, &_vboID);
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	// create buffer
	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	//// 6 verts for a rect
	//float vertexData[6 * 2];
	//// first tri
	//vertexData[0] = x + width;
	//vertexData[1] = y + width;
	//vertexData[2] = x;
	//vertexData[3] = y + height;
	//vertexData[4] = x;
	//vertexData[5] = y;
	//// second tri
	//vertexData[6] = x;
	//vertexData[7] = y;
	//vertexData[8] = x + width;
	//vertexData[9] = y;
	//vertexData[10] = x + width;
	//vertexData[11] = y + height;

	Vertex vertexData[6];
	//vertexData[0].position.x = x + width;
	//vertexData[0].position.y = y + height;
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	//vertexData[1].position.x = x;
	//vertexData[1].position.y = y + height;
	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);

	//vertexData[2].position.x = x;
	//vertexData[2].position.y = y;
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	//vertexData[3].position.x = x;
	//vertexData[3].position.y = y;
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	//vertexData[4].position.x = x + width;
	//vertexData[4].position.y = y;
	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);

	//vertexData[5].position.x = x + width;
	//vertexData[5].position.y = y + height;
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	for (int i = 0; i <6; i++)
	{
		vertexData[i].setColor(255, 0, 255, 255); 
	}

	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255); 


	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); // ptr to the begin of the buffer

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);//only sent position

	// position attribute pointer
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0); // index, size of one vertex aka 2 floats, type
	glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	// uv attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES,0,6); // mode, GL_QUAD may not work

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
