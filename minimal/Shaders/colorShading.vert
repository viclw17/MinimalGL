#version 130
in vec2 vertexPostion;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main(){
	gl_Position.xy = vertexPostion;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragmentPosition = vertexPostion;
	fragmentColor = vertexColor;
	fragmentUV = vec2(vertexUV.x, 1.0-vertexUV.y);
}