#version 150

in  vec3 fN;
in  vec3 fL;
in  vec3 fE;
in vec2 texCoord;

out vec4 fColor;

uniform sampler2D texturename;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform float Shininess;

void main() {
	
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
	
    vec3 H = normalize( L + E );
    vec4 ambient = AmbientProduct * texture(texturename, texCoord);

    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd* DiffuseProduct *texture(texturename, texCoord);
    
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    vec4 specular = Ks*SpecularProduct;

    // discard the specular highlight if the light's behind the vertex
    if( dot(L, N) < 0.0 ) {
	specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    fColor = ambient + diffuse + specular;
    fColor.a = 1.0;
} 