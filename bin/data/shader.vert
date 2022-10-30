#version 410 core

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 u_cameraPosition;

in vec4 position;
// in vec3 normal;

out float fresnelOut;

uniform float u_power;

#define TWO_PI 6.28318530718

void main(){
    vec3 unitPosition = normalize(vec3(-position.x, -position.y, position.z));
    float product = dot(unitPosition, normalize(u_cameraPosition));
    fresnelOut = pow(clamp(product, 0.0, 1.0), u_power);

    gl_Position = modelViewProjectionMatrix * position;
}
