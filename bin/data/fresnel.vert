#version 410 core

uniform mat4 modelViewProjectionMatrix;
uniform vec3 u_cameraPosition;

in vec4 position;
in vec3 normal;

out float fresnelOut;
out float bumpOut;

void main(){
    vec3 unitPosition = normalize(vec3(position.x, position.y, position.z));
    fresnelOut = dot(unitPosition, normalize(u_cameraPosition));
    bumpOut = dot(normal, normalize(-u_cameraPosition));

    gl_Position = modelViewProjectionMatrix * position;
}
