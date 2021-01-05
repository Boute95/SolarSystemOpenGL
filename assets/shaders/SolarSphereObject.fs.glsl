#version 300 es
precision mediump float;

uniform vec3 uColor;
uniform int uUseTexture;
uniform sampler2D uColorTexture;
uniform sampler2D uCloudTexture;

in vec3 vPosition;  // Position du sommet transformé dans l'espace View
in vec3 vNormal;    // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

void main() {
    if (uUseTexture == 1) {
        fFragColor = vec3(texture(uColorTexture, vTexCoords).xyz); //+ vec3(texture(uCloudTexture, vTexCoords).xyz);
    } else {
        fFragColor = uColor;
    }
}
