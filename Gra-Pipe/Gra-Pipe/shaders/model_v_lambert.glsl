#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 highPos = vec4(0,-5,0,0);
uniform vec4 lightPos = vec4(0,15,0,0);

//Atrybuty
layout (location=0) in vec3 v; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec3 n; //wektor normalny w wierzcholku
layout (location=2) in vec2 t;

//Zmienne interpolowane
out vec2 texCoord;
out vec4 normalView;
out vec4 eyeVector;
out vec4 highDirView;
out vec4 lightDirView;

void main(void) {
    vec4 vertex = vec4(v, 1);
    vec4 normal = vec4(n, 0);

    gl_Position=P*V*M*vertex;

    mat4 M1 = mat4(1);
    M1[3] = M[3];

    normalView = normalize(V*M*normal);
    eyeVector = normalize(vec4(0, 0, 0, 1) - V * M * vertex);
    highDirView = normalize(V * M1 * highPos - V * M * vertex);
    lightDirView = normalize(V * lightPos - V * M * vertex);
    texCoord = t;
}
