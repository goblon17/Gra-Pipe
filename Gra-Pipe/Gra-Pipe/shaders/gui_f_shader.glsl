#version 330

uniform sampler2D tex;

out vec4 pixelColor;

in vec2 texCoord;

void main(void) {
	vec4 c = texture(tex, texCoord);
	if(c.a == 0) {
		discard;
	}
	pixelColor = c;
}