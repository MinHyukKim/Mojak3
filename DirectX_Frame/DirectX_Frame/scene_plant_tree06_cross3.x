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


Material fleld_tree6_cross__fleld_tree6_cross_dds {
 1.000000;1.000000;1.000000;0.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "fleld_tree6_cross.dds";
 }
}

Frame scene_plant_tree06_cross3_bone01___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_plant_tree06_cross3_bone01___subgroup0 {
  24;
  172.750400;85.639923;1991.69254;,
  172.750502;85.639923;0.000000;,
  1153.75629;-85.640077;1991.69254;,
  1153.75642;-85.639974;0.000000;,
  748.89350;490.50294;1991.69254;,
  748.89363;490.50301;0.000000;,
  577.61331;-490.50298;1991.69254;,
  577.61338;-490.50307;0.000000;,
  -1153.75642;-150.775987;1928.50099;,
  -1153.75642;-150.775782;7.087402;,
  -229.292595;110.612723;1928.50099;,
  -229.292595;110.612826;7.087402;,
  -822.21888;442.15034;1928.50099;,
  -822.21882;442.15043;7.087402;,
  -560.83040;-482.31357;1928.50112;,
  -560.83027;-482.31347;7.087402;,
  -333.385062;196.570227;1842.24154;,
  -333.384986;196.570317;269.679181;,
  347.554509;-196.570394;1842.24154;,
  347.554509;-196.570278;269.679181;,
  -189.485594;-340.469760;1842.24154;,
  -189.485594;-340.469760;269.679181;,
  203.655002;340.469734;1842.24154;,
  203.655002;340.469734;269.679181;;
  12;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;,
  3;8,9,10;,
  3;11,10,9;,
  3;12,13,14;,
  3;15,14,13;,
  3;16,17,18;,
  3;19,18,17;,
  3;20,21,22;,
  3;23,22,21;;

  MeshNormals {
   24;
   -0.171994;-0.985098;0.000000;,
   -0.171994;-0.985098;0.000000;,
   -0.171994;-0.985098;0.000000;,
   -0.171994;-0.985098;0.000000;,
   -0.985098;0.171995;-0.000000;,
   -0.985098;0.171995;-0.000000;,
   -0.985098;0.171995;-0.000000;,
   -0.985098;0.171995;-0.000000;,
   0.272080;-0.962275;0.000000;,
   0.272080;-0.962275;0.000000;,
   0.272080;-0.962275;0.000000;,
   0.272079;-0.962275;0.000000;,
   -0.962275;-0.272079;0.000000;,
   -0.962275;-0.272079;0.000000;,
   -0.962275;-0.272079;0.000000;,
   -0.962275;-0.272079;0.000000;,
   -0.500000;-0.866025;0.000000;,
   -0.500000;-0.866025;0.000000;,
   -0.500000;-0.866025;0.000000;,
   -0.500000;-0.866025;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;;
   12;
   3;0,1,2;,
   3;3,2,1;,
   3;4,5,6;,
   3;7,6,5;,
   3;8,9,10;,
   3;11,10,9;,
   3;12,13,14;,
   3;15,14,13;,
   3;16,17,18;,
   3;19,18,17;,
   3;20,21,22;,
   3;23,22,21;;
  }

  MeshMaterialList {
   1;
   12;
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
   { fleld_tree6_cross__fleld_tree6_cross_dds }
  }

  MeshTextureCoords c1 {
   24;
   0.002900;0.002900;,
   0.002900;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.002900;0.002900;,
   0.002900;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.002900;0.002900;,
   0.002900;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.002900;0.002900;,
   0.002900;0.997100;,
   0.002900;0.002900;,
   0.002900;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.497100;0.002900;,
   0.497100;0.997100;,
   0.002900;0.002900;,
   0.002900;0.997100;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_plant_tree06_cross3_bone01___subgroup0 }

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