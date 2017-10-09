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


Material field_build_tircho_smallwood__field_build_tircho_smallwood_dds {
 1.000000;1.000000;1.000000;0.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "field_build_tircho_smallwood.dds";
 }
}

Frame scene_TirChonaill_wooden_barricade01_03_bone01___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_TirChonaill_wooden_barricade01_03_bone01___subgroup0 {
  19;
  15.038250;-10.197554;220.333594;,
  -15.038250;-11.562055;220.333594;,
  -15.038250;-11.562055;0.000000;,
  -15.038250;-11.562055;0.000000;,
  15.038250;-10.197455;0.000000;,
  15.038250;-10.197554;220.333594;,
  15.038250;-10.197554;220.333594;,
  15.038250;-10.197455;0.000000;,
  -1.939449;11.562045;0.000000;,
  -1.939449;11.562045;0.000000;,
  -1.939449;11.562045;220.333594;,
  15.038250;-10.197554;220.333594;,
  -15.038250;-11.562055;220.333594;,
  15.038250;-10.197554;220.333594;,
  -1.939449;11.562045;220.333594;,
  -1.939449;11.562045;0.000000;,
  -15.038250;-11.562055;0.000000;,
  -15.038250;-11.562055;220.333594;,
  -1.939449;11.562045;220.333594;;
  7;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;15,16,17;,
  3;17,18,15;;

  MeshNormals {
   19;
   0.045321;-0.998973;0.000000;,
   0.045321;-0.998973;0.000000;,
   0.045321;-0.998973;0.000000;,
   0.045324;-0.998972;0.000000;,
   0.045324;-0.998972;0.000000;,
   0.045324;-0.998972;0.000000;,
   0.788409;0.615151;-0.000000;,
   0.788409;0.615151;-0.000000;,
   0.788409;0.615151;-0.000000;,
   0.788411;0.615149;-0.000000;,
   0.788411;0.615149;-0.000000;,
   0.788411;0.615149;-0.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   -0.870101;0.492874;-0.000000;,
   -0.870101;0.492874;-0.000000;,
   -0.870101;0.492874;-0.000000;,
   -0.870101;0.492874;-0.000000;;
   7;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;17,18,15;;
  }

  MeshMaterialList {
   1;
   7;
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { field_build_tircho_smallwood__field_build_tircho_smallwood_dds }
  }

  MeshTextureCoords c1 {
   19;
   0.863700;0.789600;,
   0.859400;0.984700;,
   0.014500;0.984700;,
   0.014500;0.984700;,
   0.018700;0.789600;,
   0.863700;0.789600;,
   0.859400;0.983900;,
   0.014500;0.983900;,
   0.014500;0.788100;,
   0.014500;0.788100;,
   0.859400;0.788100;,
   0.859400;0.983900;,
   0.224600;0.176300;,
   0.117800;-0.000300;,
   0.022600;0.176400;,
   0.014500;0.788100;,
   0.014500;0.984700;,
   0.859400;0.984700;,
   0.859400;0.788100;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_TirChonaill_wooden_barricade01_03_bone01___subgroup0 }

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