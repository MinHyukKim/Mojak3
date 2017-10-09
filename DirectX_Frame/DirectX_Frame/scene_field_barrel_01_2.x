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

Frame scene_field_barrel_01_2_bone01___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_field_barrel_01_2_bone01___subgroup0 {
  210;
  -36.094093;-0.000002;0.000002;,
  -19.957592;27.949299;0.000002;,
  -3.821091;-0.000002;0.000002;,
  -52.230694;27.949299;0.000002;,
  -68.367187;-0.000002;0.000002;,
  -52.230694;-27.949302;0.000002;,
  -19.957592;-27.949302;0.000002;,
  -3.821091;-0.000002;0.000002;,
  -15.102392;36.358794;38.618301;,
  5.889309;-0.000002;38.618301;,
  -19.957592;27.949299;0.000002;,
  -19.957592;27.949299;0.000002;,
  -57.085894;36.358794;38.618301;,
  -15.102392;36.358794;38.618301;,
  -52.230694;27.949299;0.000002;,
  -52.230694;27.949299;0.000002;,
  -78.077594;-0.000002;38.618301;,
  -57.085894;36.358794;38.618301;,
  -68.367187;-0.000002;0.000002;,
  -68.367187;-0.000002;0.000002;,
  -57.085894;-36.358704;38.618301;,
  -78.077594;-0.000002;38.618301;,
  -68.367187;-0.000002;0.000002;,
  -52.230694;-27.949302;0.000002;,
  -57.085894;-36.358704;38.618301;,
  -52.230694;-27.949302;0.000002;,
  -15.102392;-36.358704;38.618301;,
  -57.085894;-36.358704;38.618301;,
  -19.957592;-27.949302;0.000002;,
  -19.957592;-27.949302;0.000002;,
  5.889309;-0.000002;38.618301;,
  -15.102392;-36.358704;38.618301;,
  -19.957592;-27.949302;0.000002;,
  -3.821091;-0.000002;0.000002;,
  5.889309;-0.000002;38.618301;,
  5.889309;-0.000002;38.618301;,
  -15.102392;36.358694;82.941402;,
  5.889309;-0.000002;82.941402;,
  5.889309;-0.000002;38.618301;,
  -15.102392;36.358794;38.618301;,
  -15.102392;36.358694;82.941402;,
  -15.102392;36.358794;38.618301;,
  -57.085894;36.358694;82.941402;,
  -15.102392;36.358694;82.941402;,
  -57.085894;36.358794;38.618301;,
  -57.085894;36.358794;38.618301;,
  -78.077594;-0.000002;82.941402;,
  -57.085894;36.358694;82.941402;,
  -57.085894;36.358794;38.618301;,
  -78.077594;-0.000002;38.618301;,
  -78.077594;-0.000002;82.941402;,
  -78.077594;-0.000002;38.618301;,
  -57.085894;-36.358704;82.941402;,
  -78.077594;-0.000002;82.941402;,
  -57.085894;-36.358704;38.618301;,
  -57.085894;-36.358704;38.618301;,
  -15.102392;-36.358704;82.941402;,
  -57.085894;-36.358704;82.941402;,
  -15.102392;-36.358704;38.618301;,
  -15.102392;-36.358704;38.618301;,
  5.889309;-0.000002;82.941402;,
  -15.102392;-36.358704;82.941402;,
  5.889309;-0.000002;38.618301;,
  5.889309;-0.000002;82.941402;,
  -19.957592;27.949299;121.559603;,
  -3.821091;-0.000002;121.559603;,
  5.889309;-0.000002;82.941402;,
  -15.102392;36.358694;82.941402;,
  -19.957592;27.949299;121.559603;,
  -15.102392;36.358694;82.941402;,
  -52.230694;27.949299;121.559603;,
  -19.957592;27.949299;121.559603;,
  -57.085894;36.358694;82.941402;,
  -57.085894;36.358694;82.941402;,
  -68.367187;-0.000002;121.559603;,
  -52.230694;27.949299;121.559603;,
  -57.085894;36.358694;82.941402;,
  -78.077594;-0.000002;82.941402;,
  -68.367187;-0.000002;121.559603;,
  -78.077594;-0.000002;82.941402;,
  -52.230694;-27.949302;121.559603;,
  -68.367187;-0.000002;121.559603;,
  -78.077594;-0.000002;82.941402;,
  -57.085894;-36.358704;82.941402;,
  -52.230694;-27.949302;121.559603;,
  -57.085894;-36.358704;82.941402;,
  -19.957592;-27.949302;121.559603;,
  -52.230694;-27.949302;121.559603;,
  -15.102392;-36.358704;82.941402;,
  -15.102392;-36.358704;82.941402;,
  -3.821091;-0.000002;121.559603;,
  -19.957592;-27.949302;121.559603;,
  -15.102392;-36.358704;82.941402;,
  5.889309;-0.000002;82.941402;,
  -3.821091;-0.000002;121.559603;,
  -36.094093;-0.000002;121.559603;,
  -3.821091;-0.000002;121.559603;,
  -19.957592;27.949299;121.559603;,
  -52.230694;27.949299;121.559603;,
  -68.367187;-0.000002;121.559603;,
  -52.230694;-27.949302;121.559603;,
  -19.957592;-27.949302;121.559603;,
  41.883706;-0.000002;0.000002;,
  69.706406;-10.126603;0.000002;,
  47.025200;-29.158502;0.000002;,
  64.565005;19.031797;0.000002;,
  36.742310;29.158499;0.000002;,
  14.061104;10.126598;0.000002;,
  19.202507;-19.031802;0.000002;,
  47.025200;-29.158502;0.000002;,
  78.077798;-13.173603;33.581101;,
  48.572106;-37.931805;33.581101;,
  47.025200;-29.158502;0.000002;,
  69.706406;-10.126603;0.000002;,
  78.077798;-13.173603;33.581101;,
  69.706406;-10.126603;0.000002;,
  71.389402;24.758198;33.581101;,
  78.077798;-13.173603;33.581101;,
  64.565005;19.031797;0.000002;,
  64.565005;19.031797;0.000002;,
  35.195306;37.931798;33.581101;,
  71.389402;24.758198;33.581101;,
  64.565005;19.031797;0.000002;,
  36.742310;29.158499;0.000002;,
  35.195306;37.931798;33.581101;,
  36.742310;29.158499;0.000002;,
  5.689709;13.173598;33.581101;,
  35.195306;37.931798;33.581101;,
  36.742310;29.158499;0.000002;,
  14.061104;10.126598;0.000002;,
  5.689709;13.173598;33.581101;,
  14.061104;10.126598;0.000002;,
  12.378105;-24.758202;33.581101;,
  5.689709;13.173598;33.581101;,
  19.202507;-19.031802;0.000002;,
  19.202507;-19.031802;0.000002;,
  48.572106;-37.931805;33.581101;,
  12.378105;-24.758202;33.581101;,
  19.202507;-19.031802;0.000002;,
  47.025200;-29.158502;0.000002;,
  48.572106;-37.931805;33.581101;,
  48.572106;-37.931805;33.581101;,
  78.077798;-13.173603;72.122899;,
  48.572106;-37.931805;72.122899;,
  78.077798;-13.173603;33.581101;,
  78.077798;-13.173603;33.581101;,
  71.389402;24.758198;72.122899;,
  78.077798;-13.173603;72.122899;,
  71.389402;24.758198;33.581101;,
  71.389402;24.758198;33.581101;,
  35.195306;37.931798;72.122899;,
  71.389402;24.758198;72.122899;,
  35.195306;37.931798;33.581101;,
  35.195306;37.931798;33.581101;,
  5.689709;13.173598;72.122899;,
  35.195306;37.931798;72.122899;,
  5.689709;13.173598;33.581101;,
  5.689709;13.173598;33.581101;,
  12.378006;-24.758202;72.122899;,
  5.689709;13.173598;72.122899;,
  5.689709;13.173598;33.581101;,
  12.378105;-24.758202;33.581101;,
  12.378006;-24.758202;72.122899;,
  12.378105;-24.758202;33.581101;,
  48.572106;-37.931805;72.122899;,
  12.378006;-24.758202;72.122899;,
  12.378105;-24.758202;33.581101;,
  48.572106;-37.931805;33.581101;,
  48.572106;-37.931805;72.122899;,
  48.572106;-37.931805;72.122899;,
  69.706406;-10.126603;105.704000;,
  47.025200;-29.158502;105.704000;,
  48.572106;-37.931805;72.122899;,
  78.077798;-13.173603;72.122899;,
  69.706406;-10.126603;105.704000;,
  78.077798;-13.173603;72.122899;,
  64.565005;19.031797;105.704000;,
  69.706406;-10.126603;105.704000;,
  71.389402;24.758198;72.122899;,
  71.389402;24.758198;72.122899;,
  36.742310;29.158499;105.704000;,
  64.565005;19.031797;105.704000;,
  71.389402;24.758198;72.122899;,
  35.195306;37.931798;72.122899;,
  36.742310;29.158499;105.704000;,
  35.195306;37.931798;72.122899;,
  14.061104;10.126598;105.704000;,
  36.742310;29.158499;105.704000;,
  35.195306;37.931798;72.122899;,
  5.689709;13.173598;72.122899;,
  14.061104;10.126598;105.704000;,
  5.689709;13.173598;72.122899;,
  19.202507;-19.031802;105.704000;,
  14.061104;10.126598;105.704000;,
  5.689709;13.173598;72.122899;,
  12.378006;-24.758202;72.122899;,
  19.202507;-19.031802;105.704000;,
  12.378006;-24.758202;72.122899;,
  47.025200;-29.158502;105.704000;,
  19.202507;-19.031802;105.704000;,
  12.378006;-24.758202;72.122899;,
  48.572106;-37.931805;72.122899;,
  47.025200;-29.158502;105.704000;,
  41.883706;-0.000002;105.704000;,
  47.025200;-29.158502;105.704000;,
  69.706406;-10.126603;105.704000;,
  64.565005;19.031797;105.704000;,
  36.742310;29.158499;105.704000;,
  14.061104;10.126598;105.704000;,
  19.202507;-19.031802;105.704000;;
  96;
  3;0,1,2;,
  3;0,3,1;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,2,6;,
  3;7,8,9;,
  3;7,10,8;,
  3;11,12,13;,
  3;11,14,12;,
  3;15,16,17;,
  3;15,18,16;,
  3;19,20,21;,
  3;22,23,24;,
  3;25,26,27;,
  3;25,28,26;,
  3;29,30,31;,
  3;32,33,34;,
  3;35,36,37;,
  3;38,39,40;,
  3;41,42,43;,
  3;41,44,42;,
  3;45,46,47;,
  3;48,49,50;,
  3;51,52,53;,
  3;51,54,52;,
  3;55,56,57;,
  3;55,58,56;,
  3;59,60,61;,
  3;59,62,60;,
  3;63,64,65;,
  3;66,67,68;,
  3;69,70,71;,
  3;69,72,70;,
  3;73,74,75;,
  3;76,77,78;,
  3;79,80,81;,
  3;82,83,84;,
  3;85,86,87;,
  3;85,88,86;,
  3;89,90,91;,
  3;92,93,94;,
  3;95,96,97;,
  3;95,97,98;,
  3;95,98,99;,
  3;95,99,100;,
  3;95,100,101;,
  3;95,101,96;,
  3;102,103,104;,
  3;102,105,103;,
  3;102,106,105;,
  3;102,107,106;,
  3;102,108,107;,
  3;102,104,108;,
  3;109,110,111;,
  3;112,113,114;,
  3;115,116,117;,
  3;115,118,116;,
  3;119,120,121;,
  3;122,123,124;,
  3;125,126,127;,
  3;128,129,130;,
  3;131,132,133;,
  3;131,134,132;,
  3;135,136,137;,
  3;138,139,140;,
  3;141,142,143;,
  3;141,144,142;,
  3;145,146,147;,
  3;145,148,146;,
  3;149,150,151;,
  3;149,152,150;,
  3;153,154,155;,
  3;153,156,154;,
  3;157,158,159;,
  3;160,161,162;,
  3;163,164,165;,
  3;166,167,168;,
  3;169,170,171;,
  3;172,173,174;,
  3;175,176,177;,
  3;175,178,176;,
  3;179,180,181;,
  3;182,183,184;,
  3;185,186,187;,
  3;188,189,190;,
  3;191,192,193;,
  3;194,195,196;,
  3;197,198,199;,
  3;200,201,202;,
  3;203,204,205;,
  3;203,205,206;,
  3;203,206,207;,
  3;203,207,208;,
  3;203,208,209;,
  3;203,209,204;;

  MeshNormals {
   210;
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   0.846196;0.488550;-0.212772;,
   0.846196;0.488550;-0.212772;,
   0.846196;0.488550;-0.212772;,
   0.846195;0.488550;-0.212772;,
   -0.000000;0.977102;-0.212773;,
   -0.000000;0.977102;-0.212773;,
   -0.000000;0.977102;-0.212773;,
   -0.000000;0.977102;-0.212773;,
   -0.846196;0.488550;-0.212772;,
   -0.846196;0.488550;-0.212772;,
   -0.846196;0.488550;-0.212772;,
   -0.846195;0.488550;-0.212772;,
   -0.846195;-0.488551;-0.212772;,
   -0.846195;-0.488551;-0.212772;,
   -0.846195;-0.488551;-0.212772;,
   -0.846196;-0.488550;-0.212771;,
   -0.846196;-0.488550;-0.212771;,
   -0.846196;-0.488550;-0.212771;,
   -0.000000;-0.977102;-0.212771;,
   -0.000000;-0.977102;-0.212771;,
   -0.000000;-0.977102;-0.212771;,
   -0.000000;-0.977102;-0.212771;,
   0.846195;-0.488551;-0.212771;,
   0.846195;-0.488551;-0.212771;,
   0.846195;-0.488551;-0.212771;,
   0.846195;-0.488550;-0.212772;,
   0.846195;-0.488550;-0.212772;,
   0.846195;-0.488550;-0.212772;,
   0.866025;0.500000;-0.000000;,
   0.866025;0.500000;-0.000000;,
   0.866025;0.500000;-0.000000;,
   0.866026;0.499999;0.000001;,
   0.866026;0.499999;0.000001;,
   0.866026;0.499999;0.000001;,
   0.000000;1.000000;0.000002;,
   0.000000;1.000000;0.000002;,
   0.000000;1.000000;0.000002;,
   0.000000;1.000000;0.000002;,
   -0.866025;0.500000;0.000001;,
   -0.866025;0.500000;0.000001;,
   -0.866025;0.500000;0.000001;,
   -0.866026;0.499999;-0.000000;,
   -0.866026;0.499999;-0.000000;,
   -0.866026;0.499999;-0.000000;,
   -0.866025;-0.500000;0.000000;,
   -0.866025;-0.500000;0.000000;,
   -0.866025;-0.500000;0.000000;,
   -0.866025;-0.500000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.866025;-0.500000;0.000000;,
   0.846195;0.488550;0.212773;,
   0.846195;0.488550;0.212773;,
   0.846195;0.488550;0.212773;,
   0.846195;0.488551;0.212772;,
   0.846195;0.488551;0.212772;,
   0.846195;0.488551;0.212772;,
   0.000000;0.977102;0.212771;,
   0.000000;0.977102;0.212771;,
   0.000000;0.977102;0.212771;,
   0.000000;0.977102;0.212771;,
   -0.846196;0.488550;0.212772;,
   -0.846196;0.488550;0.212772;,
   -0.846196;0.488550;0.212772;,
   -0.846195;0.488551;0.212773;,
   -0.846195;0.488551;0.212773;,
   -0.846195;0.488551;0.212773;,
   -0.846196;-0.488550;0.212773;,
   -0.846196;-0.488550;0.212773;,
   -0.846196;-0.488550;0.212773;,
   -0.846195;-0.488551;0.212772;,
   -0.846195;-0.488551;0.212772;,
   -0.846195;-0.488551;0.212772;,
   0.000000;-0.977102;0.212771;,
   0.000000;-0.977102;0.212771;,
   0.000000;-0.977102;0.212771;,
   0.000000;-0.977102;0.212771;,
   0.846196;-0.488550;0.212772;,
   0.846196;-0.488550;0.212772;,
   0.846196;-0.488550;0.212772;,
   0.846195;-0.488551;0.212773;,
   0.846195;-0.488551;0.212773;,
   0.846195;-0.488551;0.212773;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   -0.000000;-0.000000;-1.000000;,
   0.626467;-0.746594;-0.223911;,
   0.626467;-0.746594;-0.223911;,
   0.626467;-0.746594;-0.223911;,
   0.626469;-0.746592;-0.223914;,
   0.626469;-0.746592;-0.223914;,
   0.626469;-0.746592;-0.223914;,
   0.959803;0.169239;-0.223912;,
   0.959803;0.169239;-0.223912;,
   0.959803;0.169239;-0.223912;,
   0.959803;0.169239;-0.223912;,
   0.333336;0.915833;-0.223913;,
   0.333336;0.915833;-0.223913;,
   0.333336;0.915833;-0.223913;,
   0.333338;0.915833;-0.223912;,
   0.333338;0.915833;-0.223912;,
   0.333338;0.915833;-0.223912;,
   -0.626468;0.746593;-0.223913;,
   -0.626468;0.746593;-0.223913;,
   -0.626468;0.746593;-0.223913;,
   -0.626469;0.746592;-0.223914;,
   -0.626469;0.746592;-0.223914;,
   -0.626469;0.746592;-0.223914;,
   -0.959803;-0.169239;-0.223912;,
   -0.959803;-0.169239;-0.223912;,
   -0.959803;-0.169239;-0.223912;,
   -0.959803;-0.169239;-0.223912;,
   -0.333337;-0.915833;-0.223913;,
   -0.333337;-0.915833;-0.223913;,
   -0.333337;-0.915833;-0.223913;,
   -0.333338;-0.915832;-0.223913;,
   -0.333338;-0.915832;-0.223913;,
   -0.333338;-0.915832;-0.223913;,
   0.642787;-0.766045;0.000000;,
   0.642787;-0.766045;0.000000;,
   0.642787;-0.766045;0.000000;,
   0.642787;-0.766045;0.000000;,
   0.984808;0.173648;-0.000000;,
   0.984808;0.173648;-0.000000;,
   0.984808;0.173648;-0.000000;,
   0.984808;0.173648;-0.000000;,
   0.342021;0.939692;-0.000000;,
   0.342021;0.939692;-0.000000;,
   0.342021;0.939692;-0.000000;,
   0.342021;0.939692;-0.000000;,
   -0.642789;0.766044;-0.000000;,
   -0.642789;0.766044;-0.000000;,
   -0.642789;0.766044;-0.000000;,
   -0.642789;0.766044;-0.000000;,
   -0.984808;-0.173646;0.000000;,
   -0.984808;-0.173646;0.000000;,
   -0.984808;-0.173646;0.000000;,
   -0.984808;-0.173648;-0.000002;,
   -0.984808;-0.173648;-0.000002;,
   -0.984808;-0.173648;-0.000002;,
   -0.342021;-0.939692;-0.000001;,
   -0.342021;-0.939692;-0.000001;,
   -0.342021;-0.939692;-0.000001;,
   -0.342022;-0.939692;0.000000;,
   -0.342022;-0.939692;0.000000;,
   -0.342022;-0.939692;0.000000;,
   0.626469;-0.746593;0.223911;,
   0.626469;-0.746593;0.223911;,
   0.626469;-0.746593;0.223911;,
   0.626466;-0.746594;0.223914;,
   0.626466;-0.746594;0.223914;,
   0.626466;-0.746594;0.223914;,
   0.959803;0.169239;0.223912;,
   0.959803;0.169239;0.223912;,
   0.959803;0.169239;0.223912;,
   0.959803;0.169239;0.223912;,
   0.333338;0.915832;0.223913;,
   0.333338;0.915832;0.223913;,
   0.333338;0.915832;0.223913;,
   0.333337;0.915833;0.223912;,
   0.333337;0.915833;0.223912;,
   0.333337;0.915833;0.223912;,
   -0.626469;0.746592;0.223912;,
   -0.626469;0.746592;0.223912;,
   -0.626469;0.746592;0.223912;,
   -0.626468;0.746593;0.223914;,
   -0.626468;0.746593;0.223914;,
   -0.626468;0.746593;0.223914;,
   -0.959803;-0.169239;0.223912;,
   -0.959803;-0.169239;0.223912;,
   -0.959803;-0.169239;0.223912;,
   -0.959803;-0.169237;0.223914;,
   -0.959803;-0.169237;0.223914;,
   -0.959803;-0.169237;0.223914;,
   -0.333338;-0.915832;0.223914;,
   -0.333338;-0.915832;0.223914;,
   -0.333338;-0.915832;0.223914;,
   -0.333337;-0.915833;0.223913;,
   -0.333337;-0.915833;0.223913;,
   -0.333337;-0.915833;0.223913;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;,
   0.000000;0.000000;1.000000;;
   96;
   3;0,1,2;,
   3;0,3,1;,
   3;0,4,3;,
   3;0,5,4;,
   3;0,6,5;,
   3;0,2,6;,
   3;7,8,9;,
   3;7,10,8;,
   3;11,12,13;,
   3;11,14,12;,
   3;15,16,17;,
   3;15,18,16;,
   3;19,20,21;,
   3;22,23,24;,
   3;25,26,27;,
   3;25,28,26;,
   3;29,30,31;,
   3;32,33,34;,
   3;35,36,37;,
   3;38,39,40;,
   3;41,42,43;,
   3;41,44,42;,
   3;45,46,47;,
   3;48,49,50;,
   3;51,52,53;,
   3;51,54,52;,
   3;55,56,57;,
   3;55,58,56;,
   3;59,60,61;,
   3;59,62,60;,
   3;63,64,65;,
   3;66,67,68;,
   3;69,70,71;,
   3;69,72,70;,
   3;73,74,75;,
   3;76,77,78;,
   3;79,80,81;,
   3;82,83,84;,
   3;85,86,87;,
   3;85,88,86;,
   3;89,90,91;,
   3;92,93,94;,
   3;95,96,97;,
   3;95,97,98;,
   3;95,98,99;,
   3;95,99,100;,
   3;95,100,101;,
   3;95,101,96;,
   3;102,103,104;,
   3;102,105,103;,
   3;102,106,105;,
   3;102,107,106;,
   3;102,108,107;,
   3;102,104,108;,
   3;109,110,111;,
   3;112,113,114;,
   3;115,116,117;,
   3;115,118,116;,
   3;119,120,121;,
   3;122,123,124;,
   3;125,126,127;,
   3;128,129,130;,
   3;131,132,133;,
   3;131,134,132;,
   3;135,136,137;,
   3;138,139,140;,
   3;141,142,143;,
   3;141,144,142;,
   3;145,146,147;,
   3;145,148,146;,
   3;149,150,151;,
   3;149,152,150;,
   3;153,154,155;,
   3;153,156,154;,
   3;157,158,159;,
   3;160,161,162;,
   3;163,164,165;,
   3;166,167,168;,
   3;169,170,171;,
   3;172,173,174;,
   3;175,176,177;,
   3;175,178,176;,
   3;179,180,181;,
   3;182,183,184;,
   3;185,186,187;,
   3;188,189,190;,
   3;191,192,193;,
   3;194,195,196;,
   3;197,198,199;,
   3;200,201,202;,
   3;203,204,205;,
   3;203,205,206;,
   3;203,206,207;,
   3;203,207,208;,
   3;203,208,209;,
   3;203,209,204;;
  }

  MeshMaterialList {
   1;
   96;
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
   0,
   0,
   0,
   0;
   { field_object_01__field_object_01_dds }
  }

  MeshTextureCoords c1 {
   210;
   0.003200;0.382400;,
   0.003200;0.260200;,
   0.102700;0.323100;,
   0.102700;0.323100;,
   0.102800;0.436600;,
   0.003200;0.498800;,
   0.102800;0.436600;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.376900;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.260000;,
   0.512700;0.376900;,
   0.380200;0.376900;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.260000;,
   0.512700;0.376900;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.376900;,
   0.380200;0.498200;,
   0.240800;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.376900;,
   0.380200;0.498200;,
   0.240800;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.498200;,
   0.107200;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.498200;,
   0.107200;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.260000;,
   0.240800;0.376900;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.260000;,
   0.240800;0.376900;,
   0.107200;0.376900;,
   0.003200;0.382400;,
   0.102700;0.323100;,
   0.003200;0.260200;,
   0.102700;0.323100;,
   0.102800;0.436600;,
   0.003200;0.498800;,
   0.102800;0.436600;,
   0.003200;0.382400;,
   0.003200;0.260200;,
   0.102700;0.323100;,
   0.102700;0.323100;,
   0.102800;0.436600;,
   0.003200;0.498800;,
   0.102800;0.436600;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.376900;,
   0.512700;0.498200;,
   0.380200;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.376900;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.376900;,
   0.512700;0.498200;,
   0.380200;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.260000;,
   0.512700;0.376900;,
   0.380200;0.376900;,
   0.512700;0.376900;,
   0.380200;0.498200;,
   0.380200;0.376900;,
   0.512700;0.498200;,
   0.512700;0.260000;,
   0.380200;0.376900;,
   0.380200;0.260000;,
   0.512700;0.260000;,
   0.512700;0.376900;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.376900;,
   0.380200;0.376900;,
   0.240800;0.498200;,
   0.240800;0.376900;,
   0.380200;0.376900;,
   0.380200;0.498200;,
   0.240800;0.498200;,
   0.380200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.260000;,
   0.380200;0.260000;,
   0.380200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.498200;,
   0.107200;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.498200;,
   0.107200;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.260000;,
   0.240800;0.376900;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.107200;0.498200;,
   0.107200;0.376900;,
   0.240800;0.376900;,
   0.240800;0.498200;,
   0.107200;0.498200;,
   0.240800;0.260000;,
   0.107200;0.376900;,
   0.107200;0.260000;,
   0.240800;0.260000;,
   0.240800;0.376900;,
   0.107200;0.376900;,
   0.003200;0.382400;,
   0.102700;0.323100;,
   0.003200;0.260200;,
   0.102700;0.323100;,
   0.102800;0.436600;,
   0.003200;0.498800;,
   0.102800;0.436600;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_field_barrel_01_2_bone01___subgroup0 }

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