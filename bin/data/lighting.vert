#version 410 core

uniform mat4 modelViewProjectionMatrix;
uniform vec3 u_cameraPosition;

in vec4 position;
in vec3 normal;

out float fresnel;
out float bump;

void main(){
    vec3 unitPosition = vec3(position.x, position.y, position.z);
    bump = dot(abs(normalize(normal)), normalize(u_cameraPosition));
    bump = abs(1.0 - bump);
    
    fresnel = dot(normalize(unitPosition), normalize(u_cameraPosition));
        
    gl_Position = modelViewProjectionMatrix * position;
}
