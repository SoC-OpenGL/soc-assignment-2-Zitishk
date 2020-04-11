
#version 330

layout(location = 0 ) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout(location = 2) in vec2 aTexcord;
layout(location = 3) in vec3 aTan;

out vec2 Texcord;
out vec3 Fragpos;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
out vec3 Direclig;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 ligpos;

uniform vec3 cpos;

void main()
{
    gl_Position = projection*view*model*vec4(aPos, 1.0);
    Texcord = aTexcord;
    Fragpos = vec3(model*vec4(aPos,1.0));
    
    
    vec3 T = normalize(vec3(model * vec4(aTan, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNorm,  0.0)));

    T = normalize(T-dot(T,N)*N);
    
    vec3 B = normalize(cross(N,T));
    
    mat3 TBN = transpose(mat3(T,B,N));
    
    TangentLightPos = TBN * ligpos;
    TangentViewPos  = TBN * cpos;
    TangentFragPos  = TBN * vec3(model * vec4(aPos, 0.0));
    
    Direclig =(TBN * vec3(-0.5f, -1.0f, -1.0f)) ;
    
}
