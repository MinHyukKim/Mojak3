﻿#extension GL_EXT_gpu_shader4 : enable

uniform sampler2D textureIn;
uniform int isOutline;
uniform vec4 modifyRGB;

varying vec3 N;
varying vec3 v;
varying vec2 tex;

//픽셀 셰이더
void main (void)
{
  if (isOutline == 1)
  {
    gl_FragColor = vec4(0.0, 0.0, 0.0, texture2D(textureIn, tex.xy).a);
  } 
  else 
  {
    vec3 L = normalize(gl_LightSource[0].position.xyz - v);
    vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(L,N));
    vec4 Iamb = gl_FrontLightProduct[0].ambient;
    vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);
    vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
    Ispec = clamp(Ispec, 0.0, 1.0);
    vec4 colour = texture2D(textureIn, tex.xy).rgba;
    if (modifyRGB.a > 0) {
        float intensity = 0.3 * colour.r + 0.59 * colour.g + 0.11 * colour.b;
        intensity = intensity - 0.5;
        if (intensity < 0) intensity = 0;
        colour.rgb = ((colour.rgb * 2) * (modifyRGB.rgb * (1.0 - (intensity * 2)))) + (intensity * 2);
    }
    //gl_FrontLightModelProduct.sceneColor
    gl_FragColor = colour *
    ((vec4(0.5, 0.4, 0.3, 1) + Iamb + Idiff + Ispec) / 3.0 + 0.66);
  }
}


//버텍스 셰이더

varying vec3 N;
varying vec3 v;
varying vec2 tex;
attribute vec3 vertexPos;
attribute vec3 vertexNormal;
attribute vec2 vertexUV;
attribute vec2 boneWeight;
attribute float boneID;

uniform mat4 boneMatrix[10];

void main(void)
{
  N = normalize(gl_NormalMatrix * vertexNormal);
  vec4 newVertex;
  newVertex =  ((boneMatrix[0] * vec4(vertexPos.xyz, 1.0)) * boneWeight.x);
  newVertex += ((boneMatrix[int(boneID)] * vec4(vertexPos.xyz, 1.0)) * boneWeight.y);
  v = vec3(gl_ModelViewMatrix * newVertex);
  gl_Position = (gl_ModelViewProjectionMatrix * vec4(newVertex.xyz, 1.0));
  tex = vertexUV;
}
