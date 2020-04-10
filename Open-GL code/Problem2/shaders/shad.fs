
#version 330

in vec3 aColor;
in vec2 Texcoord;

out vec4 frag_colour;

uniform sampler2D txt;
uniform float change;
void main ()
{
  frag_colour = texture(txt, Texcoord);
}
