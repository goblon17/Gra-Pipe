#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 Vertex;
in vec4 Color;

out vec4 iColor;

void main(void) {
	iColor = Color;
	gl_Position = P * V * M * Vertex;
}