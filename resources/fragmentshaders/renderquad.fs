#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D renderTex;
uniform float exposure;
uniform bool useGamma;
uniform bool useHDR;

void main()
{
	
	const float gamma = 2.2;
	vec3 hdrColor = texture2D(renderTex, TexCoord).rgb; 
	
	vec3 mapped = vec3(0.0);
	
	//HDR processing
	if(useHDR)
	{
		mapped = vec3(1.0) - exp(-hdrColor * exposure);
	}
	else
	{
		mapped = hdrColor;
	}
	
	//gamma correction
	if(useGamma)
	{
		mapped = pow(mapped, vec3(1.0 / gamma));
	}
	
	FragColor = vec4(mapped, 1.0);
	
	
}