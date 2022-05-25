#version 330

in vec2 Vertex;

void main(void) {
	gl_Position = vec4(Vertex, 0, 1);
}