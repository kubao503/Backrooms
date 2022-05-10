#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;
uniform float dimFrac;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    float mod = 1.0;
    if (gl_TexCoord[0].y < .5 - dimFrac / 2. || gl_TexCoord[0].y > dimFrac / 2. + .5) mod = 0.7;

    gl_FragColor = vec4(pixel.xyz * mod, 1.0);
}
