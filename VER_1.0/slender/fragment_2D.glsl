#version 460

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};


struct spotLigt
{
	vec3 position;
	vec3 direction;
    float cutOff;
    float outerCutOff;
	float intensity;
	vec3 color;
	float constant;
	float Linear;
	float quadratic;

};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;
//uniforms
uniform Material material;

uniform spotLigt spotLight;

uniform vec3 camPosition;

const float density = 0.007;
const float gradient = 1.5;



void main()
{
	
    vec3 ambient = material.ambient * texture(material.diffuseTex, vs_texcoord).rgb;

    // diffuse 
    vec3 norm = normalize(vs_normal);
    vec3 lightDir = normalize(spotLight.position - vs_position);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = material.diffuse * diff * texture(material.diffuseTex, vs_texcoord).rgb;

    // specular
    vec3 viewDir = normalize(camPosition - vs_position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 30);
    vec3 specular = material.specular * spec * texture(material.specularTex, vs_texcoord).rgb;

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0, 1);
    diffuse *= intensity;
    specular *= intensity;

    // attenuation
    float distance = length(spotLight.position - vs_position);
    float attenuation = 1.f / (spotLight.constant + spotLight.Linear * distance + spotLight.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    fs_color = vec4(result, 1.0f);




}