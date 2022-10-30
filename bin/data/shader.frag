#version 410 core

vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

out vec4 outputColor;
in float fresnelOut;

uniform float u_hueStart;
uniform float u_hueDepth;
uniform float u_saturation;

void main()
{
    float hue = mod(u_hueStart + fresnelOut * u_hueDepth, 1.0);
    vec3 hsbColor = hsb2rgb(vec3(hue, u_saturation, pow(1.0 - fresnelOut, 2)));
    outputColor = vec4(hsbColor, fresnelOut);
}
