#version 130
in vec3 normal;
in vec2 st;
in vec3 light;
in vec3 light2;
out vec4 frag_colour;
uniform sampler2D basic_texture;



void main() {
	vec4 texel = texture (basic_texture, st);
	float Id = dot(light , normal); //  producto punto automaticamente 
	float Id2 = dot(light2 , normal); //  producto punto automaticamente 
	frag_colour = (Id+Id2)*texel;
}
