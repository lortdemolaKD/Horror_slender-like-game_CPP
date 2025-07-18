#version 460

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct PointLigt
{
	vec3 position;
	float intensity;
	vec3 color;
	float constant;
	float Linear;
	float quadratic;
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
uniform PointLigt pointlight;
uniform spotLigt spotLight;
uniform float sl;
uniform vec3 camPosition;

//const float density = 0.007;
const float gradient = 1.5;


//functions
vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos)
{
	vec3 posToLightDirVec = normalize(lightPos - vs_position);
	float diffuse = clamp(dot(posToLightDirVec,normalize(vs_normal)), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;
	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos, vec3 camPosition)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(camPosition - vs_position);
	float specConst = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = material.specular * specConst * texture(material.specularTex,vs_texcoord).rgb;
	return specularFinal;
}


vec3 calculatepoint(PointLigt points, Material material, vec3 vs_position, vec3 vs_normal, vec3 camPosition)
{
	vec3 ambientFinal = calculateAmbient(material);

	//diffuse light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, points.position);

	//specular light
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, points.position, camPosition);

	//attentation
	float distance = length(points.position - vs_position);
	//constant linear quadriatic
	float attentation = points.constant / (1.f + points.Linear * distance + points.quadratic * (distance * distance));

	ambientFinal *= attentation;
	diffuseFinal *= attentation;
	specularFinal *= attentation;
	
	return (ambientFinal + diffuseFinal + specularFinal);
}


vec3 calculatespot(spotLigt spot, Material material, vec3 vs_position, vec3 vs_normal,  vec3 camPosition)
{
	vec3 ambient = material.ambient * texture(material.diffuseTex, vs_texcoord).rgb;

	// diffuse 
	vec3 norm = normalize(vs_normal);
	vec3 lightDir = normalize(spot.position - vs_position);
	float diff = max(dot(norm, lightDir), 0);
	vec3 diffuse = material.diffuse * diff * texture(material.diffuseTex, vs_texcoord).rgb;

	// specular
	vec3 viewDir = normalize(camPosition - vs_position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0), 30);
	vec3 specular = material.specular * spec * texture(material.specularTex, vs_texcoord).rgb;

	// spotlight (soft edges)
	float theta = dot(lightDir, normalize(-spot.direction));
	float epsilon = (spot.cutOff - spot.outerCutOff);
	float intensity = clamp((theta - spot.outerCutOff) / epsilon, 0, 1);
	diffuse *= intensity;
	specular *= intensity;

	// attenuation
	float distance1 = length(spot.position - vs_position);
	float attenuation1 = 1.f / (spot.constant + spot.Linear * distance1 + spot.quadratic * (distance1 * distance1));
	ambient *= attenuation1;
	diffuse *= attenuation1;
	specular *= attenuation1;

	vec3 result = ambient + diffuse + specular;
	return result;
}


void main() 
{
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = (texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord));// *vec4(vs_color, 1.f);


		vec3 result;
		
			result += calculatepoint(pointlight, material, vs_position, vs_normal, camPosition);
	// phase 3: spot light
		result += calculatespot(spotLight, material, vs_position, vs_normal,  camPosition);

	
	
		//fs_color = vec4(result, 1.0f);
		fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(result, 1.0f);//* sampled //* vec4(vs_color, 1.f)
	

		
		
		
	
	
}