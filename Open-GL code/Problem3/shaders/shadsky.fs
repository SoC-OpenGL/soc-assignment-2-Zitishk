# version 330

in vec3 Texcoord;

out vec4 frag_color;
uniform samplerCube skybox;

void main()
{
    frag_color = texture(skybox,Texcoord)*vec4(0.5f,0.5f,0.5f,1.0f);
}
