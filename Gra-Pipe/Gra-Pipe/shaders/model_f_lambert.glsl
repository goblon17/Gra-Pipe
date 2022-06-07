#version 330

uniform sampler2D mainTexture;
uniform sampler2D specTexture;

uniform bool highlight = false;

uniform vec4 highColor = vec4(1,1,0,1);
uniform vec4 color=vec4(1,1,1,1);

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
in vec2 texCoord;
in vec4 normalView;
in vec4 eyeVector;
in vec4 highDirView;
in vec4 lightDirView;

void main(void) {
	vec4 mainColor = texture(mainTexture, texCoord);

	vec4 normalizedNormal = normalize(normalView);
	vec4 normalizedEyeVector = normalize(eyeVector);

	vec4 lightReflection = reflect(-lightDirView, normalizedNormal);
	vec4 highlightReflection = reflect(-highDirView, normalizedNormal);

	vec4 kd = mainColor;
	if (color.rgb != vec3(1,1,1)) {
		kd = mix(mainColor, color, 0.2);
	}
	vec4 ks1 = texture(specTexture, texCoord);
	vec4 ks2 = highColor * ks1;

	float nl1 = clamp(dot(normalizedNormal, lightDirView), 0, 1);
	float nl2 = clamp(dot(normalizedNormal, highDirView), 0, 1);

	float rv1 = pow(clamp(dot(normalizedEyeVector, lightReflection), 0, 1), 20);
	float rv2 = pow(clamp(dot(normalizedEyeVector, highlightReflection), 0, 1), 20);

	vec4 col1 = vec4(kd.rgb * nl1, kd.a) + vec4(ks1.rgb * rv1, 0);
	vec4 col2 = vec4(kd.rgb * nl2, kd.a) + vec4(ks2.rgb * rv2, 0);
	vec4 correction = mix(vec4(1,1,1,1), highColor, 0.8);
	col2 = col2 * correction;

	if(highlight) {
		pixelColor = vec4(col1.rgb + col2.rgb, 1);
	}
	else {
		pixelColor = col1;
	}
}
