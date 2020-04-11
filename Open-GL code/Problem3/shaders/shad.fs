
#version 330 core
out vec4 FragColor;

in vec2 Texcord;
in vec3 Fragpos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;
in vec3 Direclig;

//shininess

uniform sampler2D alb;
uniform sampler2D spe;
uniform sampler2D norm;
uniform sampler2D ao;
uniform int a;
uniform bool Bling;


struct Light
{
    vec3 Pos;
    vec3 color;
};

uniform Light lig;

vec3 calc(int a)
{
    
    vec3 normal = texture(norm,Texcord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    vec3 ligdir;
    
    if(a==0)
    {
        ligdir = normalize( Direclig);
    }
    else
    {
        ligdir = normalize( TangentLightPos - TangentFragPos);
    }
    
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-ligdir, normal);
    float spec = 0.0;
    if(Bling)
    {
        vec3 halfwayDir = normalize(ligdir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
    }
    else
    {   spec = pow(max(dot(viewDir, reflectDir),0.0),(16.0)); }
    
    vec3 speculation = spec * lig.color * vec3(texture(spe,Texcord));
    
    float diff = max(dot(normal,ligdir),0.0);
    vec3 diffuse =diff * lig.color * vec3(texture(alb, Texcord));
    
    vec3 ambient = vec3(0.5) * lig.color * vec3(texture(alb, Texcord))* vec3(texture(ao, Texcord));
    
    vec3 outp = (ambient+diffuse+speculation);
    
    if(a!=0)
    {
        float constant=1.0;
        float linear=0.027;
        float quadratic=0.0028;
        
        float distance    = length(lig.Pos - Fragpos);
        float attenuation = 1.0 / (constant + linear * distance +
                                   quadratic * (distance * distance));
        outp*=attenuation;
    }
    
    if(a==2)
    {
        ligdir = normalize( lig.Pos - Fragpos);
        float theta = dot(ligdir,normalize(lig.Pos));
        float cutoff =0.9989;
        float outercutOff = 0.998;
        float epsilon   = cutoff - outercutOff;
        float intensity = clamp((theta - outercutOff) / epsilon, 0.0, 1.0);
        
        outp*= intensity;
    }
    
    return outp;
}


void main()
{
    
    
    vec3 result =vec3(0);
    
    result+= calc(a);
    //result = Direclig;
    //FragColor = texture(norm,Texcord);
    FragColor = vec4(result,1.0);
}
