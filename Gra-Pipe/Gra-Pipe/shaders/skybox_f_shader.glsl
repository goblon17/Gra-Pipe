#version 330

uniform samplerCube skybox;

in vec3 iTexCoord;

out vec4 pixelColor;

void main(void) {
	pixelColor = texture(skybox, iTexCoord);
}