#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 camPos;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform bool hasMetallic;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;
uniform bool hasAO;

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

struct PointLight
{
	vec3 position;
	vec3 color;
};


#define MAX_NR_DIR_LIGHTS 1
uniform DirectionalLight dirlights[MAX_NR_DIR_LIGHTS];
uniform int NR_DIR_LIGHTS;

#define MAX_NR_POINT_LIGHTS 10
uniform PointLight pointlights[MAX_NR_POINT_LIGHTS];
uniform int NR_POINT_LIGHTS;

#define PI 3.1415926535

vec3 fresnelShlick(float _cosTheta, vec3 _F0);
float distributionGGX(vec3 _N, vec3 _H, float _roughness);
float geometrySchlickGGX(float _NdotV, float _roughness);
float geometrySmith(vec3 _N, vec3 _V, vec3 _L, float _roughness);
vec3 getNormalFromMap();

void main()
{
	vec3 albedo = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));
	float metallic = 0.0;
	if(hasMetallic)
	{
		metallic = texture(metallicMap, TexCoords).r;
	}
	float roughness = texture(roughnessMap, TexCoords).r;
	float ao = 0.0;
	if(hasAO)
	{
		ao = texture(aoMap, TexCoords).r;
	}
	vec3 N = getNormalFromMap();
	vec3 V = normalize(camPos - WorldPos);
	vec3 Lo = vec3(0.0);
	
	for(int i = 0; i < NR_DIR_LIGHTS; i++)
	{
		vec3 L = normalize(-dirlights[i].direction);
		vec3 H = normalize(V + L);
		
		vec3 radiance = dirlights[i].color;
		vec3 f0 = vec3(0.04);
		f0 = mix(f0, albedo, metallic);
		vec3 F = fresnelShlick(max(dot(H, V), 0.0), f0);
		float NDF = distributionGGX(N, H, roughness);
		float G = geometrySmith(N, V, L, roughness);
		
		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular = numerator / max(denominator, 0.001);
		
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		
		kD *= 1.0 - metallic;
		
		float NdotL = max(dot(N, L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}
	
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		vec3 L = normalize(pointlights[i].position - WorldPos);
		vec3 H = normalize(V + L);
		
		float distance = length(pointlights[i].position - WorldPos);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = pointlights[i].color * attenuation;
		vec3 f0 = vec3(0.04);
		f0 = mix(f0, albedo, metallic);
		vec3 F = fresnelShlick(max(dot(H, V), 0.0), f0);
		float NDF = distributionGGX(N, H, roughness);
		float G = geometrySmith(N, V, L, roughness);
		
		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
		vec3 specular = numerator / max(denominator, 0.001);
		
		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		
		kD *= 1.0 - metallic;
		
		float NdotL = max(dot(N, L), 0.0);
		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}
	
	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;
	
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0/2.2));
	
	FragColor = vec4(color, 1.0);
}

vec3 fresnelShlick(float _cosTheta, vec3 _F0)
{
	return _F0 + (1.0 - _F0) * pow(1.0 - _cosTheta, 5.0);
}

float distributionGGX(vec3 _N, vec3 _H, float _roughness)
{
	float a = _roughness * _roughness;
	float a2 = a*a;
	float NdotH = max(dot(_N, _H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;
	
	return num / denom;
}

float geometrySchlickGGX(float _NdotV, float _roughness)
{
	float r = (_roughness + 1.0);
	float k = (r*r) / 8.0;
	
	float num = _NdotV;
	float denom = _NdotV * (1.0 - k) + k;
	
	return num / denom;
}

float geometrySmith(vec3 _N, vec3 _V, vec3 _L, float _roughness)
{
	float NdotV = max(dot(_N, _V), 0.0);
	float NdotL = max(dot(_N, _L), 0.0);
	float ggx2 = geometrySchlickGGX(NdotV, _roughness);
	float ggx1 = geometrySchlickGGX(NdotL, _roughness);
	
	return ggx1 * ggx2;

}

vec3 getNormalFromMap()
{
	vec3 tangentNormal = texture(normalMap, TexCoords).xyz * 2.0 - 1.0;
	
	vec3 Q1 = dFdx(WorldPos);
	vec3 Q2 = dFdy(WorldPos);
	vec2 st1 = dFdx(TexCoords);
	vec2 st2 = dFdy(TexCoords);
	
	vec3 N = normalize(Normal);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	
	mat3 TBN = mat3(T, B, N);
	
	return normalize(TBN * tangentNormal);

}




