#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position[2];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int light_type;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_pos, vec3 light_color);

void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25 * material_kd;

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    vec3 light_color = vec3(1,1,1);
    float light = ambient_light + point_light_contribution(light_position[0], light_color) + point_light_contribution(light_position[1], light_color);
    vec3 color = object_color * light;

    // TODO(student): Write pixel out color
    out_color = vec4(color, 1);

}

float point_light_contribution(vec3 light_pos, vec3 light_color)
{
    float color;


    vec3 V = normalize(eye_position - world_position);
    vec3 L = normalize(light_pos - world_position);
    vec3 R = reflect (-L, world_normal);

    float diffuse_light = material_kd * max (dot(world_normal,L), 0);
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light =  material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    float light_att_factor = 1;
    if (light_type == 1) {
        float cut_off = 0.5;
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);
        if (spot_light > cos(cut_off))
        {
            // Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            light_att_factor = pow(linear_att, 2);
        }
        else
        {
            light_att_factor = 0;
        }
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    float d = distance(light_pos, world_position);
    color = 1 / (d*d) * light_att_factor * (diffuse_light + specular_light);

	return color;
}
