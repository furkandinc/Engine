#version 150
//Becareful of line ending, only lf accepted

#define NOTEXTURE -1
#define HASTEXTURE 1

// per-fragment interpolated values from the vertex shader
in vec3 fN;
in vec3 fL;
in vec3 fE;
in vec2 fUv;

out vec4 fColor;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform float Shininess;

uniform int TextureMode;
uniform sampler2D TextureID;

void main() 
{ 
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);

    vec3 H = normalize( L + E );
    
    vec4 ambient = AmbientProduct;

    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd*DiffuseProduct;
    
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    vec4 specular = Ks*SpecularProduct;

    // discard the specular highlight if the light's behind the vertex
    if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

	if(TextureMode == HASTEXTURE){
		ambient = AmbientProduct * texture(TextureID, fUv);
		diffuse = Kd * DiffuseProduct * texture(TextureID, fUv);
	}
	
	fColor = ambient + diffuse + specular;
	fColor.a = 1.0;
} 

