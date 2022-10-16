#ifdef GL_ES
precision highp float;
#endif

#define PROCESSING_TEXTURE_SHADER

uniform float u_time;
uniform float u_wrap;
uniform float u_sine;
uniform vec2 u_resolution;

const float PI = 3.14159265359;

uniform sampler2D texture;

vec3 rgb2hsb( in vec3 c ){
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(c.bg, K.wz),
			vec4(c.gb, K.xy),
			step(c.b, c.g));
	vec4 q = mix(vec4(p.xyw, c.r),
			vec4(c.r, p.yzx),
			step(p.x, c.r));
	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;
	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
			d / (q.x + e),
			q.x);
}

vec3 hsb2rgb( in vec3 c ){
	vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
					6.0)-3.0)-1.0,
			0.0,
			1.0 );
	rgb = rgb*rgb*(3.0-2.0*rgb);
	return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(void) {
	vec2 st = gl_FragCoord.xy / u_resolution;
	vec2 cPos = -1.0 + 2.0 * st;
	float cLength = length(cPos);
	vec2 add = (cPos / cLength) * cos(cLength * 12.0 - u_time * 4.0) * 0.03;
	add *= u_sine * 10.0;

	vec4 textureColor = texture2D(texture, st + add * 3);
	vec3 textureHsb = rgb2hsb(textureColor.rgb);
	textureHsb.x = fract(textureHsb.x + (add.x) * 3);
	vec3 color = hsb2rgb(textureHsb);

	gl_FragColor = vec4(color, 1.0);
}
