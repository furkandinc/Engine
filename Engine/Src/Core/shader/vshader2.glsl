#version 150 

in vec4 vPosition;
in vec3 vNormal;
in vec2 vUv;

// output values that will be interpolated per-fragment
out vec3 fN;
out vec3 fE;
out vec3 fL;
out vec2 fUv;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 Projection;

void main()
{
    fN = normalize(vec3(ModelView*vec4(vNormal,0.0)));
    fE = -normalize(vec3(ModelView*vPosition));
    fL = normalize(vec3(LightPosition-ModelView*vPosition)); //light in camera coords
	
	fUv = vUv;

    gl_Position = Projection*ModelView*vPosition;
}
