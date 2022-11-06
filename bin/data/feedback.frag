#version 410 core
//precision highp int;

//uniform sampler2D tex;

//uniform float u_scaleFactor;
out vec4 outputColor;
in vec4 colorOut;

void main(void) {
  /*vec2 tc0 = colorOut.st + vec2(-gl_PointCoord.s, -gl_PointCoord.t);
  vec2 tc1 = colorOut.st + vec2(         0.0, -gl_PointCoord.t);
  vec2 tc2 = colorOut.st + vec2(+gl_PointCoord.s, -gl_PointCoord.t);
  vec2 tc3 = colorOut.st + vec2(-gl_PointCoord.s,          0.0);
  vec2 tc4 = colorOut.st + vec2(         0.0,          0.0);
  vec2 tc5 = colorOut.st + vec2(+gl_PointCoord.s,          0.0);
  vec2 tc6 = colorOut.st + vec2(-gl_PointCoord.s, +gl_PointCoord.t);
  vec2 tc7 = colorOut.st + vec2(         0.0, +gl_PointCoord.t);
  vec2 tc8 = colorOut.st + vec2(+gl_PointCoord.s, +gl_PointCoord.t);

  vec4 col0 = texture(tex, tc0);
  vec4 col1 = texture(tex, tc1);
  vec4 col2 = texture(tex, tc2);
  vec4 col3 = texture(tex, tc3);
  vec4 col4 = texture(tex, tc4);
  vec4 col5 = texture(tex, tc5);
  vec4 col6 = texture(tex, tc6);
  vec4 col7 = texture(tex, tc7);
  vec4 col8 = texture(tex, tc8);

  vec4 sum = (1.0 * col0 + (2.0 * u_scaleFactor) * col1 + 1.0 * col2 +
              (2.0 * u_scaleFactor) * col3 + (4.0 * u_scaleFactor) * col4 + (2.0 * u_scaleFactor) * col5 +
              1.0 * col6 + (2.0 * u_scaleFactor) * col7 + 1.0 * col8) / 16.0;
   */
  
    //outputColor = vec4(sum.rgb, 1.0) * colorOut;
    outputColor = colorOut;
    // outputColor = vec4(color, colorOut.y, colorOut.z, 1.0);
}
