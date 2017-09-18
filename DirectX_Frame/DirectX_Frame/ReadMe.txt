#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D textureIn;
uniform int isOutline;
uniform vec4 modifyRGB;	//색상

varying vec3 N;		// 빛?
varying vec3 v;		// 눈?
varying vec2 tex;	// 텍스쳐

//픽셀 셰이더
void main (void)
{
  if (isOutline == 1)
  {
    gl_FragColor = vec4(0.0, 0.0, 0.0, texture2D(textureIn, tex.xy).a);
  } 
  else 
  {
    vec3 L = normalize(gl_LightSource[0].position.xyz - v);						//빛
    vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)	//눈
    vec3 R = normalize(-reflect(L,N));											//??
    vec4 Iamb = gl_FrontLightProduct[0].ambient;								//빛의색상
    
	//반사광?
	vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);

    vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
    Ispec = clamp(Ispec, 0.0, 1.0);

    vec4 colour = texture2D(textureIn, tex.xy).rgba;	//텍스쳐 색상

    if (modifyRGB.a > 0) //색상값의 알파가 0보다 크면
	{
		//텍스쳐의 색상값 설정
        float intensity = 0.3 * colour.r + 0.59 * colour.g + 0.11 * colour.b;
        intensity = intensity - 0.5;
        if (intensity < 0) intensity = 0;
        colour.rgb = ((colour.rgb * 2) * (modifyRGB.rgb * (1.0 - (intensity * 2)))) + (intensity * 2);
    }

    //gl_FrontLightModelProduct.sceneColor
    gl_FragColor = colour * ((vec4(0.5, 0.4, 0.3, 1) + Iamb + Idiff + Ispec) / 3.0 + 0.66);
  }
}


//버텍스 셰이더

아웃
varying vec3 N;							//노말
varying vec3 v;							//포지션
varying vec2 tex;						//텍스쳐
인
attribute vec3 vertexPos;				//점위치
attribute vec3 vertexNormal;			//노말위치
attribute vec2 vertexUV;				//텍스쳐
attribute vec2 boneWeight;				//뼈가중치
attribute float boneID;

uniform mat4 boneMatrix[10];

void main(void)
{
  N = normalize(gl_NormalMatrix * vertexNormal); //output.
  vec4 newVertex;
  newVertex =  ((boneMatrix[0] * vec4(vertexPos.xyz, 1.0)) * boneWeight.x);
  newVertex += ((boneMatrix[int(boneID)] * vec4(vertexPos.xyz, 1.0)) * boneWeight.y);
  v = vec3(gl_ModelViewMatrix * newVertex);
  gl_Position = (gl_ModelViewProjectionMatrix * vec4(newVertex.xyz, 1.0));
  tex = vertexUV;
}
