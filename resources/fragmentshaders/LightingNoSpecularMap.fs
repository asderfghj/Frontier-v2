#version 330 core
out vec4 FragColor;

struct Material 
{
	sampler2D diffuseMat;
	sampler2D normalMap;
	bool hasNormalmap;
	float shininess;
};

struct PointLight
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
	
};

struct DirectionalLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D shadowMap;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutoff;
	float outercutoff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

vec3 CalculateDirectionalLight(DirectionalLight _light, vec3 _normal, vec3 _viewDir);
vec3 CalculatePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);
vec3 CalculateSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir);
float ShadowCalculation(DirectionalLight _light, vec4 _fragPosLightSpace, vec3 _normal, vec3 _lightdir);
vec3 getNormalFromMap();

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

uniform vec3 viewPos;
uniform Material material;

#define MAX_NR_DIR_LIGHTS 1
uniform DirectionalLight dirlight[MAX_NR_DIR_LIGHTS];
uniform int NR_DIR_LIGHTS;

#define MAX_NR_POINT_LIGHTS 50
uniform PointLight pointlights[MAX_NR_POINT_LIGHTS];
uniform int NR_POINT_LIGHTS;

#define MAX_NR_SPOT_LIGHTS 50
uniform SpotLight spotlights[MAX_NR_SPOT_LIGHTS];
uniform int NR_SPOT_LIGHTS;

void main()
{
	vec3 norm = vec3(0.0);

	if(material.hasNormalmap)
	{	
		norm = getNormalFromMap();
	}
	else
	{
		norm = normalize(Normal);
	}
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
	{
		result += CalculateDirectionalLight(dirlight[i], norm, viewDir);
	}
	
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalculatePointLight(pointlights[i], norm, FragPos, viewDir);
	}
	
	for (int i = 0; i < NR_SPOT_LIGHTS; i++)
	{
		result += CalculateSpotLight(spotlights[i], norm, FragPos, viewDir);
	}
	
	FragColor = vec4(result, 1.0);
	//FragColor = vec4(texture2D(material.normalMap, TexCoords).xyz, 1.0);
	
	/*float gamma = 2.2;
	FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));*/
	
}

vec3 CalculateDirectionalLight(DirectionalLight _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(-_light.direction);
	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float diff = max(dot(_normal, lightDir), 0.0);
	
	//vec3 reflectDir = reflect(-lightDir, _normal);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), material.shininess);
	
	vec3 ambient = vec3(texture2D(material.diffuseMat, TexCoords).xyz) * _light.ambient;
	vec3 diffuse = diff * _light.diffuse;
	vec3 specular = spec * _light.specular;
	
	float shadow = ShadowCalculation(_light, FragPosLightSpace, _normal, lightDir);
	
	return ((ambient + (1.0 - shadow)) * (diffuse + specular)) * texture2D(material.diffuseMat, TexCoords).rgb;
}

vec3 CalculatePointLight(PointLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	vec3 halfwayDir = normalize(lightDir + _viewDir);
	float diff = max(dot(_normal, lightDir), 0.0);
	
	//vec3 reflectDir = reflect(-lightDir, _normal);
	float spec = pow(max(dot(_normal, halfwayDir), 0.0), material.shininess);
	
	float distance = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * distance + _light.quadratic * (distance * distance));
	
	vec3 ambient = vec3(texture2D(material.diffuseMat, TexCoords).xyz) * _light.ambient;
	vec3 diffuse = vec3(texture2D(material.diffuseMat, TexCoords).xyz) * diff * _light.diffuse;
	vec3 specular = vec3(texture2D(material.diffuseMat, TexCoords).xyz) * spec * _light.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (ambient + diffuse + specular);

}

vec3 CalculateSpotLight(SpotLight _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
    vec3 lightDir = normalize(_light.position - _fragPos);
	vec3 halfwayDir = normalize(lightDir + _viewDir);
	
    float diff = max(dot(_normal, lightDir), 0.0);
	
	
	
    float spec = pow(max(dot(_normal, halfwayDir), 0.0), material.shininess);
    float distance = length(_light.position - _fragPos);
    float attenuation = 1.0 / (_light.constant + _light.linear * distance + _light.quadratic * (distance * distance));    
    float theta = dot(lightDir, normalize(-_light.direction)); 
    float epsilon = _light.cutoff - _light.outercutoff;
    float intensity = clamp((theta - _light.outercutoff) / epsilon, 0.0, 1.0);
    //vec3 ambient = _light.ambient * vec3(texture(material.diffuseMat, TexCoord).xyz);
    vec3 diffuse = _light.diffuse * diff * vec3(texture(material.diffuseMat, TexCoords).xyz);
    vec3 specular = _light.specular * spec * vec3(texture(material.diffuseMat, TexCoords).xyz);
    //ambient *=  intensity * attenuation;
    diffuse *=  intensity * attenuation;
    specular *=  intensity * attenuation;
    return (/*ambient + */diffuse + specular);
}

float ShadowCalculation(DirectionalLight _light, vec4 _fragPosLightSpace, vec3 _normal, vec3 _lightdir)
{
	vec3 projCoords = _fragPosLightSpace.xyz / _fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(_light.shadowMap, projCoords.xy).r; 
	float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(_normal, _lightdir)), 0.005);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(_light.shadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(_light.shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0; 
		}
	}
	shadow /= 9.0;
	
	if(projCoords.z > 1.0)
	{
		shadow = 0.0;
	}

	return shadow;
}

vec3 getNormalFromMap()
{
	vec3 tangentNormal = texture(material.normalMap, TexCoords).xyz * 2.0 - 1.0;
	
	vec3 Q1 = dFdx(FragPos);
	vec3 Q2 = dFdy(FragPos);
	vec2 st1 = dFdx(TexCoords);
	vec2 st2 = dFdy(TexCoords);
	
	vec3 N = normalize(Normal);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	
	mat3 TBN = mat3(T, B, N);
	
	return normalize(TBN * tangentNormal);

}


