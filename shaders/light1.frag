varying vec4 vert_pos;

uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;
uniform vec2 lightPos2;

void main()
{
	//Ambient light
	vec4 ambient = vec4(0.7, 0.7, 0.7, 1.9);
	vec4 ambient2 = vec4(0.7, 0.7, 0.7, 1.9);
	
	//Convert light to view coords
	vec2 light = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;
	vec2 light2 = (gl_ModelViewProjectionMatrix * vec4(lightPos2, 0, 1)).xy;
	
	//Calculate the vector from light to pixel (Make circular)
	vec2 lightToFrag = light - vert_pos.xy;
	lightToFrag.y = lightToFrag.y / 1.7;

	vec2 lightToFrag2 = light2 - vert_pos.xy;
	lightToFrag2.y = lightToFrag2.y / 1.7;

	//Length of the vector (distance)
	float vecLength = clamp(length(lightToFrag) * 3, 0, 1);
	float vecLenght2 = clamp(length(lightToFrag2) * 3, 0, 1);

    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color and lighting
	if(hasTexture == true)
	{
		gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1)) * (clamp(ambient2 + vec4(1 - vecLenght2, 1-vecLenght2, 1-vecLenght2, 1), 0, 1));	
	}
	else
	{
		gl_FragColor = gl_Color;
	}
}

//gl_Color * pixel * (clamp(ambient + vec4(1-vecLength, 1-vecLength, 1-vecLength, 1), 0, 1));
//vec4(1, 0, 0, 1);