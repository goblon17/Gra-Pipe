#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 Vertex;
in vec3 texCoord;

out vec3 iTexCoord;

void main(void) {
	iTexCoord = texCoord;
	gl_Position = P * V * M * Vertex;
}