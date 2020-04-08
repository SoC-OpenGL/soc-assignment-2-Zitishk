#version 330 core

in vec3 Texcord;

out vec4 FragColor;

uniform samplerCube cubet;

void main()
{
    //Fragcolor = vec4(Texcord,1.0);
    FragColor = vec4(Texcord,1.0);
}
