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


Material field_object_01__field_object_01_dds {
 1.000000;1.000000;1.000000;0.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "field_object_01.dds";
 }
}

Frame scene_field_box_01_2_bone01___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_field_box_01_2_bone01___subgroup0 {
  48;
  -107.913587;-50.018403;0.000002;,
  -107.913587;49.981597;0.000002;,
  -7.913590;49.981597;0.000002;,
  -7.913590;-50.018403;0.000002;,
  -107.913587;-50.018403;100.000000;,
  -7.913590;-50.018403;100.000000;,
  -7.913590;49.981597;100.000000;,
  -107.913587;49.981597;100.000000;,
  -107.913587;-50.018403;0.000002;,
  -7.913590;-50.018403;0.000002;,
  -7.913590;-50.018403;100.000000;,
  -107.913587;-50.018403;100.000000;,
  -7.913590;-50.018403;0.000002;,
  -7.913590;49.981597;0.000002;,
  -7.913590;49.981597;100.000000;,
  -7.913590;-50.018403;100.000000;,
  -7.913590;49.981597;0.000002;,
  -107.913587;49.981597;0.000002;,
  -107.913587;49.981597;100.000000;,
  -7.913590;49.981597;100.000000;,
  -107.913587;49.981597;0.000002;,
  -107.913587;-50.018403;0.000002;,
  -107.913587;-50.018403;100.000000;,
  -107.913587;49.981597;100.000000;,
  24.214013;-57.081702;0.000002;,
  -6.249988;26.617699;0.000002;,
  77.449312;57.081702;0.000002;,
  107.913408;-26.617602;0.000002;,
  24.214013;-57.081702;89.071002;,
  107.913408;-26.617602;89.071002;,
  77.449312;57.081702;89.071002;,
  -6.249988;26.617699;89.071002;,
  24.214013;-57.081702;0.000002;,
  107.913408;-26.617602;0.000002;,
  107.913408;-26.617602;89.071002;,
  24.214013;-57.081702;89.071002;,
  107.913408;-26.617602;0.000002;,
  77.449312;57.081702;0.000002;,
  77.449312;57.081702;89.071002;,
  107.913408;-26.617602;89.071002;,
  77.449312;57.081702;0.000002;,
  -6.249988;26.617699;0.000002;,
  -6.249988;26.617699;89.071002;,
  77.449312;57.081702;89.071002;,
  -6.249988;26.617699;0.000002;,
  24.214013;-57.081702;0.000002;,
  24.214013;-57.081702;89.071002;,
  -6.249988;26.617699;89.071002;;
  24;
  3;0,1,2;,
  3;2,3,0;,
  3;4,5,6;,
  3;6,7,4;,
  3;8,9,10;,
  3;10,11,8;,
  3;12,13,14;,
  3;14,15,12;,
  3;16,17,18;,
  3;18,19,16;,
  3;20,21,22;,
  3;22,23,20;,
  3;24,25,26;,
  3;26,27,24;,
  3;28,29,30;,
  3;30,31,28;,
  3;32,33,34;,
  3;34,35,32;,
  3;36,37,38;,
  3;38,39,36;,
  3;40,41,42;,
  3;42,43,40;,
  3;44,45,46;,
  3;46,47,44;;

  MeshNormals {
   48;
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   1.000000;-0.000000;0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -0.000000;1.000000;-0.000000;,
   -1.000000;0.000000;-0.000000;,
   -1.000000;0.000000;-0.000000;,
   -1.000000;0.000000;-0.000000;,
   -1.000000;0.000000;-0.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.342020;-0.939693;0.000000;,
   0.342020;-0.939693;0.000000;,
   0.342020;-0.939693;0.000000;,
   0.342020;-0.939693;0.000000;,
   0.939692;0.342021;-0.000000;,
   0.939692;0.342021;-0.000000;,
   0.939692;0.342021;-0.000000;,
   0.939692;0.342021;-0.000000;,
   -0.342020;0.939693;-0.000000;,
   -0.342020;0.939693;-0.000000;,
   -0.342020;0.939693;-0.000000;,
   -0.342020;0.939693;-0.000000;,
   -0.939693;-0.342019;0.000000;,
   -0.939693;-0.342019;0.000000;,
   -0.939693;-0.342019;0.000000;,
   -0.939693;-0.342019;0.000000;;
   24;
   3;0,1,2;,
   3;2,3,0;,
   3;4,5,6;,
   3;6,7,4;,
   3;8,9,10;,
   3;10,11,8;,
   3;12,13,14;,
   3;14,15,12;,
   3;16,17,18;,
   3;18,19,16;,
   3;20,21,22;,
   3;22,23,20;,
   3;24,25,26;,
   3;26,27,24;,
   3;28,29,30;,
   3;30,31,28;,
   3;32,33,34;,
   3;34,35,32;,
   3;36,37,38;,
   3;38,39,36;,
   3;40,41,42;,
   3;42,43,40;,
   3;44,45,46;,
   3;46,47,44;;
  }

  MeshMaterialList {
   1;
   24;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
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
   { field_object_01__field_object_01_dds }
  }

  MeshTextureCoords c1 {
   48;
   0.513000;0.255400;,
   0.513000;0.002100;,
   0.259800;0.002100;,
   0.259900;0.255500;,
   0.259900;0.255500;,
   0.513000;0.255400;,
   0.513000;0.002100;,
   0.259800;0.002100;,
   0.002100;0.255300;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002400;0.255500;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002100;0.255300;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002400;0.255500;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.513000;0.255400;,
   0.513000;0.002100;,
   0.259800;0.002100;,
   0.259900;0.255500;,
   0.259900;0.255500;,
   0.513000;0.255400;,
   0.513000;0.002100;,
   0.259800;0.002100;,
   0.002100;0.255300;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002400;0.255500;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002100;0.255300;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;,
   0.002400;0.255500;,
   0.255600;0.255400;,
   0.255600;0.002100;,
   0.002300;0.002100;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_field_box_01_2_bone01___subgroup0 }

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