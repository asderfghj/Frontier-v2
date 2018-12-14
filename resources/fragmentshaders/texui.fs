#version 330 core
in vec2 TexCoord;


uniform vec4 color;
uniform sampler2D texture;

void main()
{
	gl_FragColor = texture2D(texture, TexCoord);
	if(gl_FragColor.a < 0.5)
	{
		discard;
	}
	
}