#version 410 core

in vec4 position;
in vec4 globalColor;

uniform mat4 modelViewProjectionMatrix;
out vec4 colorOut;

void main(){
    colorOut = globalColor;
    gl_Position = modelViewProjectionMatrix * position;
}
