#version 300 es
precision mediump float;

// Vertex
layout(location = 1) in vec3 aVertexPosition;
layout(location = 2) in vec3 aVertexNormal;
layout(location = 3) in vec2 aVertexTexCoords;

// Uniforms
uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

// Sorties du shader
out vec3 vPosition;  // Position du sommet transformé dans l'espace View
out vec3 vNormal;    // Normale du sommet transformé dans l'espace View
out vec2 vTexCoords; // Coordonnées de texture du sommet

void main() {
    vec4 vertexPosition = vec4(aVertexPosition, 1);
    vec4 vertexNormal = vec4(aVertexNormal, 0);

    mat4 MVMatrix =  uViewMatrix * uModelMatrix;
    mat4 MVPMatrix = uProjMatrix * MVMatrix;
    mat4 normalMatrix = transpose(inverse(MVMatrix));
    
    vPosition = vec3(MVMatrix * vertexPosition);
    vNormal = vec3(normalMatrix * vertexNormal);
    vTexCoords = aVertexTexCoords;

    gl_Position = MVPMatrix * vertexPosition;
};