#version 300 es
precision mediump float;

uniform sampler2D uTexture;
uniform sampler2D uCloudTexture;

in vec3 vPosition;  // Position du sommet transformé dans l'espace View
in vec3 vNormal;    // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

void main() {
    // fFragColor = vec3(texture(uTexture, vTexCoords).xyz) + vec3(texture(uCloudTexture, vTexCoords).xyz);
    fFragColor = vec3(1.0, 1.0, 1.0);
}
