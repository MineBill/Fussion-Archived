#version 460 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTextureCoordinate;
layout (location = 2) in vec3 aNormal;

out vec2 sTextureCoordinates;
out vec3 sNormal;
out vec3 sFragmentPosition;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main() {
    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);
    sTextureCoordinates = vec2(aTextureCoordinate.x, 1.0 - aTextureCoordinate.y);
    sFragmentPosition = vec3(uModelMatrix * vec4(aPosition, 1.0));

    // PERFORMANCE: This should be done on the CPU
    sNormal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
}
