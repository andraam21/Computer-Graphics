#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D texture_1;
uniform sampler2D texture_2;

// Output
out vec2 texcoord;
out vec4 out_color;


void main()
{
    // TODO(student): Pass v_texture_coord as output to fragment shader
    texcoord = v_texture_coord;
    vec4 color1 = texture2D(texture_1, texcoord);
    vec4 color2 = texture2D(texture_2, texcoord);  
    vec3 color = mix(color1.xyz, color2.xyz, 0.75f);
    //out_color = vec4(vec3(0, texcoord.x, 0) + color, 1.f);
    vec3 pos = v_position + vec3(0, color1.r * 15, 0);

    gl_Position = Projection * View * Model * vec4(pos, 1.0f);
}
