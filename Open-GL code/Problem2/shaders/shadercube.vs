#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexcord;

uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;

out vec2 Texcord;
out vec2 pos;

void main()
{
    gl_Position = proj * model * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Texcord = aTexcord;
    pos = vec2(aPos.x,aPos.y);
}
