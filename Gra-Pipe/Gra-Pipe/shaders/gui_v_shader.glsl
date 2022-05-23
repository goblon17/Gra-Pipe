#version 330

uniform mat4 M;
uniform float aspectRatio;

in vec2 Vertex;

out vec2 texCoord;

void main(void) {
	vec2 t = vec2((Vertex.x + 1) / 2, (-Vertex.y + 1) / 2);
	texCoord = t;
	vec2 v = vec2(Vertex.x / aspectRatio, Vertex.y);
	gl_Position = M * vec4(v, 0, 1);
}