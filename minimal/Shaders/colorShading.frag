#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;

out vec4 color;
uniform float time;

void main(){
	color = vec4(
	fragmentColor.r * (cos(fragmentPosition.x*10+time)+1)*.5,
	fragmentColor.g * (cos(fragmentPosition.y*10+time)+1)*.5,
	fragmentColor.b * (cos(fragmentPosition.x*5+time)+1)*.5,
	1);

	
	//color = fragmentColor + 
	//vec4(
	//.5*(cos(time)+1),
	//.5*(cos(time+2)+1),
	//.5*(sin(time+1)+1),
	//1);
}