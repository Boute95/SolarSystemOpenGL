#version 300 es
precision mediump float;

// Vertex
layout(location = 1) in vec3 aVertexPosition;

out vec3 texCoords;

uniform mat4 uProjMatrixSB;
uniform mat4 uViewMatrixSB;

void main()
{
    texCoords = aVertexPosition;
    gl_Position = uProjMatrixSB * uViewMatrixSB * vec4(aVertexPosition , 1.0);
}  