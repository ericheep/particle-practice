#version 410 core

out vec4 outputColor;
in float fresnelOut;
in float bumpOut;

uniform float u_hueStart;
uniform float u_hueDepth;
uniform float u_hueCurve;

uniform float u_saturationStart;
uniform float u_saturationDepth;
uniform float u_saturationCurve;

uniform float u_brightnessStart;
uniform float u_brightnessDepth;
uniform float u_brightnessCurve;

uniform float u_bumpDepth;

vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main()
{
    float huePower = pow(1.0 - fresnelOut, u_hueCurve);
    float hue = mod(u_hueStart + huePower * u_hueDepth, 1.0);
    
    float saturationPower = pow(fresnelOut, u_saturationCurve);
    float saturation = clamp(u_saturationStart + saturationPower * u_saturationCurve, 0.0, 1.0);
    
    float brightnessPower = pow(1.0 - fresnelOut, u_brightnessCurve);
    float brightness = clamp(u_brightnessStart + brightnessPower * u_brightnessCurve, 0.0, 1.0);
    
    vec3 hsbColor = hsb2rgb(vec3(hue + bumpOut * u_bumpDepth, saturation, brightness));
    outputColor = vec4(hsbColor, fresnelOut);
}
