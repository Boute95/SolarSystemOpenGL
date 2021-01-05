#version 300 es
precision mediump float;

out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube uCubeMapTexture; // cubemap texture sampler
uniform float uLightnessFactor;


void main() {             
    FragColor = texture(uCubeMapTexture, texCoords) * uLightnessFactor;
}