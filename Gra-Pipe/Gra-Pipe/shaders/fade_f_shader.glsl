#version 330

uniform float alfa;

out vec4 pixelColor;

void main(void) {
	if(alfa == 0) {
		discard;
	}
	vec4 c = vec4(0, 0, 0, alfa);
	pixelColor = c;
}