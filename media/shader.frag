#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;
uniform float renderDist;

void main()
{
    vec3 color = vec3(0.78, 0.74, 0.59);
    float maxAngle = 3.14159265 / 4.;

    float angle = atan(abs((gl_TexCoord[0].y - 0.5) * 2.)) * maxAngle * 4. / 3.14159265;
    float distDim = 5.3 * (1. / tan(angle)) / -renderDist + 1.;

    gl_FragColor = vec4(.7 * distDim * color, 1.0);
}
