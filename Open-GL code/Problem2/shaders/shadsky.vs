#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 proj;
uniform mat4 view;

out vec3 Texcord;

void main()
{
    vec4 pos = proj * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = pos.xyww;
    Texcord = aPos;
}
