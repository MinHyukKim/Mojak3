xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template AnimTicksPerSecond {
 <9e415a43-7ba6-4a73-8743-b73d47e88476>
 DWORD AnimTicksPerSecond;
}

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}

template FloatKeys {
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}


Material nature_trunk02__nature_trunk02_dds {
 1.000000;1.000000;1.000000;0.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "nature_trunk02.dds";
 }
}

Frame scene_wooden_barricade_00_bone01___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_wooden_barricade_00_bone01___subgroup0 {
  30;
  -14.202750;0.311767;127.456102;,
  0.015750;-14.118034;129.424307;,
  14.202750;0.629667;131.751398;,
  14.202750;0.629667;131.751398;,
  0.449650;14.118067;124.464397;,
  -14.202750;0.311767;127.456102;,
  -7.383650;-7.264633;0.000001;,
  7.616350;-7.264633;0.000001;,
  0.015750;-14.118034;129.424307;,
  0.015750;-14.118034;129.424307;,
  -14.202750;0.311767;127.456102;,
  -7.383650;-7.264633;0.000001;,
  7.616350;-7.264633;0.000001;,
  7.616350;7.735367;0.000001;,
  14.202750;0.629667;131.751398;,
  14.202750;0.629667;131.751398;,
  0.015750;-14.118034;129.424307;,
  7.616350;-7.264633;0.000001;,
  7.616350;7.735367;0.000001;,
  -7.383650;7.735367;0.000001;,
  0.449650;14.118067;124.464397;,
  0.449650;14.118067;124.464397;,
  14.202750;0.629667;131.751398;,
  7.616350;7.735367;0.000001;,
  -7.383650;7.735367;0.000001;,
  -7.383650;-7.264633;0.000001;,
  -14.202750;0.311767;127.456102;,
  -14.202750;0.311767;127.456102;,
  0.449650;14.118067;124.464397;,
  -7.383650;7.735367;0.000001;;
  10;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;15,16,17;,
  3;18,19,20;,
  3;21,22,23;,
  3;24,25,26;,
  3;27,28,29;;

  MeshNormals {
   30;
   -0.149368;-0.012324;0.988705;,
   -0.149368;-0.012324;0.988705;,
   -0.149368;-0.012324;0.988705;,
   -0.143754;0.352906;0.924550;,
   -0.143754;0.352906;0.924550;,
   -0.143754;0.352906;0.924550;,
   -0.000000;-0.998601;-0.052879;,
   -0.000000;-0.998601;-0.052879;,
   -0.000000;-0.998601;-0.052879;,
   -0.712543;-0.701620;0.003584;,
   -0.712543;-0.701620;0.003584;,
   -0.712543;-0.701620;0.003584;,
   0.998753;-0.000000;-0.049929;,
   0.998753;-0.000000;-0.049929;,
   0.998753;-0.000000;-0.049929;,
   0.720224;-0.693719;0.005562;,
   0.720224;-0.693719;0.005562;,
   0.720224;-0.693719;0.005562;,
   -0.000000;0.998688;-0.051214;,
   -0.000000;0.998688;-0.051214;,
   -0.000000;0.998688;-0.051214;,
   0.699225;0.714892;0.003601;,
   0.699225;0.714892;0.003601;,
   0.699225;0.714892;0.003601;,
   -0.998572;-0.000000;-0.053425;,
   -0.998572;-0.000000;-0.053425;,
   -0.998572;-0.000000;-0.053425;,
   -0.685145;0.728384;0.005768;,
   -0.685145;0.728384;0.005768;,
   -0.685145;0.728384;0.005768;;
   10;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;;
  }

  MeshMaterialList {
   1;
   10;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { nature_trunk02__nature_trunk02_dds }
  }

  MeshTextureCoords c1 {
   30;
   0.902300;0.386700;,
   0.902300;0.113300;,
   0.613300;0.113300;,
   0.613300;0.113300;,
   0.613300;0.386700;,
   0.902300;0.386700;,
   0.230500;0.988300;,
   0.371100;0.988300;,
   0.230500;0.027300;,
   0.230500;0.027300;,
   0.121100;0.043000;,
   0.230500;0.988300;,
   0.371100;0.988300;,
   0.488300;0.988300;,
   0.371100;0.019500;,
   0.371100;0.019500;,
   0.230500;0.027300;,
   0.371100;0.988300;,
   0.011700;0.988300;,
   0.097700;0.988300;,
   0.011700;0.074200;,
   0.488300;0.074200;,
   0.371100;0.019500;,
   0.488300;0.988300;,
   0.097700;0.988300;,
   0.230500;0.988300;,
   0.121100;0.043000;,
   0.121100;0.043000;,
   0.011700;0.074200;,
   0.097700;0.988300;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_wooden_barricade_00_bone01___subgroup0 }

  AnimationKey S {
   1;
   2;
   0;3;0.020000,0.020000,0.020000;;,
   16000;3;0.020000,0.020000,0.020000;;;
  }

  AnimationKey R {
   0;
   2;
   0;4;-0.000000,-0.000000,0.707107,0.707107;;,
   16000;4;-0.000000,-0.000000,0.707107,0.707107;;;
  }

  AnimationKey T {
   2;
   2;
   0;3;0.000000,0.000000,0.000000;;,
   16000;3;0.000000,0.000000,0.000000;;;
  }
 }
}