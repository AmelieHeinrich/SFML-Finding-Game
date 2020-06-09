varying vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;

void main() 
{
	vec4 ambient = vec4(0.01, 0.01, 0.01, 0);

	vec2 light = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;

	vec2 lightToFrag = light - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	float vecLength = clamp(length(lightToFrag) * 3, 0, 1);

	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	if(hasTexture == true)
	{
		gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1));	
	}
	else
	{
		gl_FragColor = gl_Color;
	}	
}