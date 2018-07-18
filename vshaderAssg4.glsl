#version 150

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out  vec3 fN;
out  vec3 fE;
out  vec3 fL;
out vec2 texCoord;

uniform mat4 ModelView;
uniform vec4 LightPosition;
uniform mat4 Projection;
uniform mat4 ModelObj;

void main(){
	fN = normalize(vec3(ModelView*ModelObj*vec4(vNormal,0.0)));
	fE = -normalize(vec3(ModelView*ModelObj*vPosition));
	fL = normalize(vec3(ModelView*LightPosition-ModelView*vPosition)); //light in camera coords
	texCoord = vTexCoord;
	gl_Position = Projection*ModelView*ModelObj*vPosition;
}