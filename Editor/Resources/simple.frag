#version 460 core
out vec4 FragColor;

struct PointLight 
{
    float constant;
    float linear;
    float quadratic;
    vec3 position;
    vec3 color;
};

struct SpotLight 
{
    float min_cutoff;
    float max_cutoff;
    float constant;
    float linear;
    float quadratic;
    vec3 direction;
    vec3 position;
    vec3 color;
};

struct DirectionalLight 
{
    float ambient;
    vec3 direction;
    vec3 color;
};

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

in vec2 sTextureCoordinates;
in vec3 sNormal;
in vec3 sFragmentPosition;

struct LightData 
{
    float ambient_strength;
    float specular_strength;
};

uniform LightData uLightData;

uniform Material uMaterial;

uniform vec3 uCameraPosition;
uniform bool uUseLighting;

uniform DirectionalLight uDirectionalLight;
#define NUMBER_OF_POINT_LIGHTS 1
uniform PointLight uPointLights[NUMBER_OF_POINT_LIGHTS];
uniform int uNumberOfPointLights; 

#define NUMBER_OF_SPOT_LIGHTS 1
uniform SpotLight uSpotLights[NUMBER_OF_SPOT_LIGHTS];
uniform int uNumberOfSpotLights;

vec3 CalculateDirectionalLight()
{
    vec3 light_direction = normalize(-uDirectionalLight.direction);
    vec3 normal = normalize(sNormal);

    float diff = max(dot(normal, light_direction), 0.0);

    vec3 view_direction = normalize(uCameraPosition - sFragmentPosition);
    vec3 reflected = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflected), 0.0), uMaterial.shininess);

    vec3 diffuse = uDirectionalLight.color * diff * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    vec3 specular = uDirectionalLight.color * spec * texture(uMaterial.specular, sTextureCoordinates).rgb;
    vec3 ambient = uDirectionalLight.ambient * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    return diffuse + specular + ambient;
}

vec3 CalculatePointLight(PointLight light)
{
    vec3 light_direction = normalize(light.position - sFragmentPosition);
    vec3 normal = normalize(sNormal);

    float diff = max(dot(normal, light_direction), 0.0);
    
    vec3 view_direction = normalize(uCameraPosition - sFragmentPosition);
    vec3 reflected = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflected), 0.0), uMaterial.shininess);

    float dist = distance(light.position, sFragmentPosition);
    float attenuaton = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    vec3 diffuse = light.color * diff * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    vec3 specular = light.color * spec * texture(uMaterial.specular, sTextureCoordinates).rgb;
    vec3 ambient = uDirectionalLight.ambient * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    return (diffuse + specular + ambient) * attenuaton;
}

vec3 CalculateSpotLight(SpotLight light)
{
    vec3 light_direction = normalize(light.position - sFragmentPosition);
    vec3 normal = normalize(sNormal);

    float diff = max(dot(normal, light_direction), 0.0);
    
    vec3 view_direction = normalize(uCameraPosition - sFragmentPosition);
    vec3 reflected = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflected), 0.0), uMaterial.shininess);

    float dist = distance(light.position, sFragmentPosition);
    float attenuaton = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    float theta = dot(light_direction, normalize(-light.direction));
    // Subtraction order is reveresed because cos(max_angle) < cos(min_angle)
    float epsilon = light.min_cutoff - light.max_cutoff;
    float intensity = clamp((theta - light.max_cutoff) / epsilon, 0.0, 1.0);

    vec3 diffuse = light.color * diff * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    vec3 specular = spec * texture(uMaterial.specular, sTextureCoordinates).rgb;
    vec3 ambient = uDirectionalLight.ambient * texture(uMaterial.diffuse, sTextureCoordinates).rgb;
    return (diffuse + specular + ambient) * attenuaton * intensity;
}

void main() 
{
    if (uUseLighting) {
        vec3 color = vec3(0);

        color += CalculateDirectionalLight();

        for (int i = 0; i < uNumberOfPointLights; i++) {
            color += CalculatePointLight(uPointLights[i]);
        }

        for (int i = 0; i < uNumberOfSpotLights; i++) {
            color += CalculateSpotLight(uSpotLights[i]);
        }

        FragColor = vec4(color, 1.0);
    } else {
        FragColor = vec4(texture(uMaterial.diffuse, sTextureCoordinates).rgb, 1.0);
    }
}
