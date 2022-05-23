#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform float Size;

in vec3 Vertex;

out vec3 iTexCoord;

void main(void) {
	iTexCoord = Vertex;
	mat4 nV = V;
	nV[3].xyz = vec3(0, 0, 0);
	gl_Position = P * nV * M * vec4(Vertex * Size, 1);
}