#version 410 core
precision highp int;

out vec4 outputColor;
in float fresnelOut;
in float bumpOut;

uniform float u_hueStart;
uniform float u_hueDepth;
uniform float u_hueCurve;

uniform float u_saturationAmount;
uniform float u_saturationCurve;

uniform float u_brightnessAmount;
uniform float u_brightnessCurve;

uniform float u_bumpDepth;

vec3 hsb2rgb( in vec3 c ) {
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main() {
    float fresnel = clamp(fresnelOut, 0.0, 1.0);
    
    float huePower = pow(fresnel, u_hueCurve);
    float hue = mod(u_hueStart + huePower * u_hueDepth + bumpOut * u_bumpDepth, 1.0);
    
    float saturationDepth = 1.0 - u_saturationAmount;
    float saturationPower = pow(fresnel, u_saturationCurve);
    float saturation = clamp(u_saturationAmount + saturationPower * saturationDepth, 0.0, 1.0);
    
    float brightnessDepth = 1.0 - u_brightnessAmount;
    float brightnessPower = pow(fresnel, u_brightnessCurve);
    float brightness = clamp(u_brightnessAmount + brightnessPower * brightnessDepth, 0.0, 1.0);
    
    vec3 hsbColor = hsb2rgb(vec3(hue, saturation, brightness));
    outputColor = vec4(hsbColor, bumpOut);
}
