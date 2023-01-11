#version 420 core
out vec4 frag_color;

in vec2 s_texcoord;
in vec3 s_normal;
in vec3 s_frag_position;

struct LightData {
    float ambient_strength;
    float specular_strength;
    vec3 light_color;
    
    // PointLight
    vec3 position;
    float constant;
    float linear;
    float quadratic;

    // SpotLight
    float min_cutoff;
    float max_cutoff;
    
    // DirectionalLight & SpotLight
    vec3 direction;
};
uniform LightData u_light_data;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material u_material;

uniform vec3 u_camera;
uniform bool u_use_lighting;

void main() {
    if (u_use_lighting) {
        vec3 ambient = u_light_data.ambient_strength * texture(u_material.diffuse, s_texcoord).rgb;
        vec3 normal = normalize(s_normal);
        vec3 light_direction = normalize(u_light_data.position - s_frag_position);
//        vec3 light_direction = normalize(-u_light_data.direction);

        float diff = max(dot(normal, light_direction), 0.0);
        vec3 diffuse_color = texture(u_material.diffuse, s_texcoord).rgb;
        vec3 diffuse = diff * diffuse_color * u_light_data.light_color;

        vec3 view_direction = normalize(u_camera - s_frag_position);
        vec3 reflected = reflect(-light_direction, normal);

        float spec = pow(max(dot(view_direction, reflected), 0.0), u_material.shininess);
        vec3 specular_color = texture(u_material.specular, s_texcoord).rgb * spec;
        vec3 specular = specular_color * u_light_data.specular_strength * u_light_data.light_color;
        
        vec3 emission = texture(u_material.emission, s_texcoord).rgb * texture(u_material.diffuse, s_texcoord).rgb;
        
        float dist = distance(u_light_data.position, s_frag_position);
        float attenuaton = 1.0 / (u_light_data.constant + u_light_data.linear * dist + u_light_data.quadratic * dist * dist);

        float theta = dot(light_direction, normalize(-u_light_data.direction));
        // Subtraction order is reveresed because cos(max_angle) < cos(min_angle)
        float epsilon = u_light_data.min_cutoff - u_light_data.max_cutoff;
        float intensity = clamp((theta - u_light_data.max_cutoff) / epsilon, 0.0, 1.0);

        vec3 result = (diffuse + ambient + specular + emission) * attenuaton * intensity;
        frag_color = vec4(result, 1.0);
    } else {
        frag_color = vec4(texture(u_material.diffuse, s_texcoord).rgb, 1.0);
    }
}
