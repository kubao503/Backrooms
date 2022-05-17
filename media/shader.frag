#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;

void main()
{
    // vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // float mod = 1.0;
    // if (gl_TexCoord[0].y < .5 - dimFrac / 2. || gl_TexCoord[0].y > dimFrac / 2. + .5) mod = 0.7;

    vec3 color = vec3(0.5098, 0.4196, 0.1922);
    float maxAngle = 3.14159265 / 4.;

    float angle = atan(abs((gl_TexCoord[0].y - 0.5) * 2.)) * maxAngle * 4. / 3.14159265;
    float distDim = -0.049 * (1. / tan(angle)) + .75f;
    float dimFactor = distDim;

    gl_FragColor = vec4(dimFactor * color, 1.0);
    // gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);

}
