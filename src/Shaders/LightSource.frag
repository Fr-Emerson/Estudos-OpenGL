#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 LightColor;
uniform vec3 LightPos;

void main()
{

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * LightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;

    vec4 result = texture(ourTexture, TexCoord);
    result = vec4(ambient + diffuse, 1.0) * result;
    FragColor = result;
}