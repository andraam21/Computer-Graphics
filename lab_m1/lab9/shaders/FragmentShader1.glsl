#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms



// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.

    vec4 color1 = texture2D(texture_1, texcoord).rrrr;
    vec4 color2 = texture2D(texture_2, texcoord);  
    vec3 color = mix(color1.xyz, color2.xyz, 0.0f);
	out_color = vec4(color, 1.f);


}
