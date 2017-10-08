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

Frame scene_wooden_barricade_03_bone___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_wooden_barricade_03_bone___subgroup0 {
  114;
  -100.139136;-14.194146;127.723392;,
  -84.567840;-1.151747;126.425690;,
  -97.376237;14.148654;131.527296;,
  -97.376237;14.148654;131.527296;,
  -113.099738;1.496254;127.419699;,
  -100.139136;-14.194146;127.723392;,
  -91.907341;-7.990546;0.000001;,
  -90.730438;6.963154;0.000001;,
  -84.567840;-1.151747;126.425690;,
  -84.567840;-1.151747;126.425690;,
  -100.139136;-14.194146;127.723392;,
  -91.907341;-7.990546;0.000001;,
  -90.730438;6.963154;0.000001;,
  -105.684134;8.140054;0.000001;,
  -97.376237;14.148654;131.527296;,
  -97.376237;14.148654;131.527296;,
  -84.567840;-1.151747;126.425690;,
  -90.730438;6.963154;0.000001;,
  -105.684134;8.140054;0.000001;,
  -106.861037;-6.813646;0.000001;,
  -113.099738;1.496254;127.419699;,
  -113.099738;1.496254;127.419699;,
  -97.376237;14.148654;131.527296;,
  -105.684134;8.140054;0.000001;,
  -106.861037;-6.813646;0.000001;,
  -91.907341;-7.990546;0.000001;,
  -100.139136;-14.194146;127.723392;,
  -100.139136;-14.194146;127.723392;,
  -113.099738;1.496254;127.419699;,
  -106.861037;-6.813646;0.000001;,
  -125.174336;12.184854;104.164704;,
  -121.680243;16.695754;115.897702;,
  -124.495334;25.042352;106.273299;,
  -125.174336;12.184854;104.164704;,
  -1.134239;11.690954;75.004800;,
  1.680862;3.344353;84.629203;,
  -125.174336;12.184854;104.164704;,
  -124.495334;25.042352;106.273299;,
  -1.134239;11.690954;75.004800;,
  -124.495334;25.042352;106.273299;,
  2.359863;16.201754;86.737798;,
  -1.134239;11.690954;75.004800;,
  -124.495334;25.042352;106.273299;,
  -121.680243;16.695754;115.897702;,
  2.359863;16.201754;86.737798;,
  -121.680243;16.695754;115.897702;,
  1.680862;3.344353;84.629203;,
  2.359863;16.201754;86.737798;,
  -121.680243;16.695754;115.897702;,
  -125.174336;12.184854;104.164704;,
  1.680862;3.344353;84.629203;,
  1.680862;3.344353;84.629203;,
  121.315661;11.139754;31.162304;,
  124.809766;15.650554;42.895306;,
  1.680862;3.344353;84.629203;,
  -1.134239;11.690954;75.004800;,
  121.315661;11.139754;31.162304;,
  -1.134239;11.690954;75.004800;,
  121.994765;23.997152;33.270899;,
  121.315661;11.139754;31.162304;,
  -1.134239;11.690954;75.004800;,
  2.359863;16.201754;86.737798;,
  121.994765;23.997152;33.270899;,
  2.359863;16.201754;86.737798;,
  124.809766;15.650554;42.895306;,
  121.994765;23.997152;33.270899;,
  2.359863;16.201754;86.737798;,
  1.680862;3.344353;84.629203;,
  124.809766;15.650554;42.895306;,
  121.315661;11.139754;31.162304;,
  121.994765;23.997152;33.270899;,
  124.809766;15.650554;42.895306;,
  -122.587149;-12.198546;38.628102;,
  -123.046643;-25.042347;40.874499;,
  -125.716134;-16.638347;50.490605;,
  -122.587149;-12.198546;38.628102;,
  -9.795937;-5.267046;69.790298;,
  -7.126442;-13.670946;60.174195;,
  -122.587149;-12.198546;38.628102;,
  -7.126442;-13.670946;60.174195;,
  -123.046643;-25.042347;40.874499;,
  -123.046643;-25.042347;40.874499;,
  -7.126442;-13.670946;60.174195;,
  -10.255440;-18.110848;72.036698;,
  -123.046643;-25.042347;40.874499;,
  -10.255440;-18.110848;72.036698;,
  -125.716134;-16.638347;50.490605;,
  -125.716134;-16.638347;50.490605;,
  -10.255440;-18.110848;72.036698;,
  -9.795937;-5.267046;69.790298;,
  -125.716134;-16.638347;50.490605;,
  -9.795937;-5.267046;69.790298;,
  -122.587149;-12.198546;38.628102;,
  -9.795937;-5.267046;69.790298;,
  122.587162;-13.885347;117.016499;,
  125.716160;-9.445546;105.154099;,
  -9.795937;-5.267046;69.790298;,
  125.716160;-9.445546;105.154099;,
  -7.126442;-13.670946;60.174195;,
  -7.126442;-13.670946;60.174195;,
  125.716160;-9.445546;105.154099;,
  125.256666;-22.289347;107.400499;,
  -7.126442;-13.670946;60.174195;,
  125.256666;-22.289347;107.400499;,
  -10.255440;-18.110848;72.036698;,
  -10.255440;-18.110848;72.036698;,
  125.256666;-22.289347;107.400499;,
  122.587162;-13.885347;117.016499;,
  -10.255440;-18.110848;72.036698;,
  122.587162;-13.885347;117.016499;,
  -9.795937;-5.267046;69.790298;,
  125.716160;-9.445546;105.154099;,
  122.587162;-13.885347;117.016499;,
  125.256666;-22.289347;107.400499;;
  38;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;15,16,17;,
  3;18,19,20;,
  3;21,22,23;,
  3;24,25,26;,
  3;27,28,29;,
  3;30,31,32;,
  3;33,34,35;,
  3;36,37,38;,
  3;39,40,41;,
  3;42,43,44;,
  3;45,46,47;,
  3;48,49,50;,
  3;51,52,53;,
  3;54,55,56;,
  3;57,58,59;,
  3;60,61,62;,
  3;63,64,65;,
  3;66,67,68;,
  3;69,70,71;,
  3;72,73,74;,
  3;75,76,77;,
  3;78,79,80;,
  3;81,82,83;,
  3;84,85,86;,
  3;87,88,89;,
  3;90,91,92;,
  3;93,94,95;,
  3;96,97,98;,
  3;99,100,101;,
  3;102,103,104;,
  3;105,106,107;,
  3;108,109,110;,
  3;111,112,113;;

  MeshNormals {
   114;
   0.206119;-0.149872;0.966982;,
   0.206119;-0.149872;0.966982;,
   0.206119;-0.149872;0.966982;,
   -0.162934;-0.115624;0.979839;,
   -0.162934;-0.115624;0.979839;,
   -0.162934;-0.115624;0.979839;,
   0.995487;-0.078348;-0.053554;,
   0.995487;-0.078348;-0.053554;,
   0.995487;-0.078348;-0.053554;,
   0.642308;-0.766435;0.004171;,
   0.642308;-0.766435;0.004171;,
   0.642308;-0.766435;0.004171;,
   0.078361;0.995649;-0.050434;,
   0.078361;0.995649;-0.050434;,
   0.078361;0.995649;-0.050434;,
   0.767397;0.641161;0.003748;,
   0.767397;0.641161;0.003748;,
   0.767397;0.641161;0.003748;,
   -0.995471;0.078346;-0.053850;,
   -0.995471;0.078346;-0.053850;,
   -0.995471;0.078346;-0.053850;,
   -0.627556;0.778560;0.004072;,
   -0.627556;0.778560;0.004072;,
   -0.627556;0.778560;0.004072;,
   -0.078348;-0.995495;-0.053401;,
   -0.078348;-0.995495;-0.053401;,
   -0.078348;-0.995495;-0.053401;,
   -0.771017;-0.636803;0.003780;,
   -0.771017;-0.636803;0.003780;,
   -0.771017;-0.636803;0.003780;,
   -0.958823;0.004064;0.283976;,
   -0.958823;0.004064;0.283976;,
   -0.958823;0.004064;0.283976;,
   -0.149403;-0.768213;-0.622518;,
   -0.149403;-0.768213;-0.622518;,
   -0.149403;-0.768213;-0.622518;,
   -0.224906;0.169245;-0.959569;,
   -0.224906;0.169245;-0.959569;,
   -0.224906;0.169245;-0.959569;,
   0.009348;0.932420;-0.361256;,
   0.009348;0.932420;-0.361256;,
   0.009348;0.932420;-0.361256;,
   0.149404;0.768211;0.622519;,
   0.149404;0.768211;0.622519;,
   0.149404;0.768211;0.622519;,
   0.224906;-0.169246;0.959569;,
   0.224906;-0.169246;0.959569;,
   0.224906;-0.169246;0.959569;,
   -0.009346;-0.932417;0.361264;,
   -0.009346;-0.932417;0.361264;,
   -0.009346;-0.932417;0.361264;,
   0.195237;-0.933506;0.300748;,
   0.195237;-0.933506;0.300748;,
   0.195237;-0.933506;0.300748;,
   -0.218975;-0.767938;-0.601932;,
   -0.218975;-0.767938;-0.601932;,
   -0.218975;-0.767938;-0.601932;,
   -0.331522;0.169711;-0.928058;,
   -0.331522;0.169711;-0.928058;,
   -0.331522;0.169711;-0.928058;,
   -0.195237;0.933506;-0.300748;,
   -0.195237;0.933506;-0.300748;,
   -0.195237;0.933506;-0.300748;,
   0.218975;0.767937;0.601933;,
   0.218975;0.767937;0.601933;,
   0.218975;0.767937;0.601933;,
   0.331522;-0.169707;0.928059;,
   0.331522;-0.169707;0.928059;,
   0.331522;-0.169707;0.928059;,
   0.958823;-0.004071;-0.283974;,
   0.958823;-0.004071;-0.283974;,
   0.958823;-0.004071;-0.283974;,
   -0.965878;-0.010705;-0.258778;,
   -0.965878;-0.010705;-0.258778;,
   -0.965878;-0.010705;-0.258778;,
   0.127741;0.764104;-0.632319;,
   0.127741;0.764104;-0.632319;,
   0.127741;0.764104;-0.632319;,
   0.178423;-0.175713;-0.968138;,
   0.178423;-0.175713;-0.968138;,
   0.178423;-0.175713;-0.968138;,
   0.144235;-0.938646;-0.313272;,
   0.144235;-0.938646;-0.313272;,
   0.144235;-0.938646;-0.313272;,
   -0.127743;-0.764100;0.632323;,
   -0.127743;-0.764100;0.632323;,
   -0.127743;-0.764100;0.632323;,
   -0.178423;0.175711;0.968138;,
   -0.178423;0.175711;0.968138;,
   -0.178423;0.175711;0.968138;,
   -0.144233;0.938649;0.313265;,
   -0.144233;0.938649;0.313265;,
   -0.144233;0.938649;0.313265;,
   -0.058776;0.939924;0.336287;,
   -0.058776;0.939924;0.336287;,
   -0.058776;0.939924;0.336287;,
   0.184645;0.764852;-0.617177;,
   0.184645;0.764852;-0.617177;,
   0.184645;0.764852;-0.617177;,
   0.320770;-0.174305;-0.930980;,
   0.320770;-0.174305;-0.930980;,
   0.320770;-0.174305;-0.930980;,
   0.058777;-0.939923;-0.336290;,
   0.058777;-0.939923;-0.336290;,
   0.058777;-0.939923;-0.336290;,
   -0.184647;-0.764846;0.617184;,
   -0.184647;-0.764846;0.617184;,
   -0.184647;-0.764846;0.617184;,
   -0.320769;0.174306;0.930980;,
   -0.320769;0.174306;0.930980;,
   -0.320769;0.174306;0.930980;,
   0.965877;0.010705;0.258781;,
   0.965877;0.010705;0.258781;,
   0.965877;0.010705;0.258781;;
   38;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;,
   3;36,37,38;,
   3;39,40,41;,
   3;42,43,44;,
   3;45,46,47;,
   3;48,49,50;,
   3;51,52,53;,
   3;54,55,56;,
   3;57,58,59;,
   3;60,61,62;,
   3;63,64,65;,
   3;66,67,68;,
   3;69,70,71;,
   3;72,73,74;,
   3;75,76,77;,
   3;78,79,80;,
   3;81,82,83;,
   3;84,85,86;,
   3;87,88,89;,
   3;90,91,92;,
   3;93,94,95;,
   3;96,97,98;,
   3;99,100,101;,
   3;102,103,104;,
   3;105,106,107;,
   3;108,109,110;,
   3;111,112,113;;
  }

  MeshMaterialList {
   1;
   38;
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
   { nature_trunk02__nature_trunk02_dds }
  }

  MeshTextureCoords c1 {
   114;
   0.707000;0.371100;,
   0.863300;0.285200;,
   0.777300;0.128900;,
   0.777300;0.128900;,
   0.621100;0.214800;,
   0.707000;0.371100;,
   0.371100;0.988300;,
   0.488300;0.988300;,
   0.371100;0.050800;,
   0.371100;0.050800;,
   0.253900;0.035200;,
   0.371100;0.988300;,
   0.011700;0.988300;,
   0.128900;0.988300;,
   0.011700;0.011700;,
   0.488300;0.011700;,
   0.371100;0.050800;,
   0.488300;0.988300;,
   0.128900;0.988300;,
   0.246100;0.988300;,
   0.128900;0.043000;,
   0.128900;0.043000;,
   0.011700;0.011700;,
   0.128900;0.988300;,
   0.246100;0.988300;,
   0.371100;0.988300;,
   0.253900;0.035200;,
   0.253900;0.035200;,
   0.128900;0.043000;,
   0.246100;0.988300;,
   0.892600;0.238300;,
   0.697000;0.336100;,
   0.697000;0.140500;,
   0.480500;0.011700;,
   0.488300;0.988300;,
   0.339800;0.988300;,
   0.019500;0.011700;,
   0.168000;0.011700;,
   0.019500;0.988300;,
   0.168000;0.011700;,
   0.168000;0.988300;,
   0.019500;0.988300;,
   0.168000;0.011700;,
   0.324200;0.011700;,
   0.168000;0.988300;,
   0.324200;0.011700;,
   0.339800;0.988300;,
   0.168000;0.988300;,
   0.324200;0.011700;,
   0.480500;0.011700;,
   0.339800;0.988300;,
   0.339800;0.988300;,
   0.480500;0.011700;,
   0.324200;0.011700;,
   0.339800;0.988300;,
   0.488300;0.988300;,
   0.480500;0.011700;,
   0.019500;0.988300;,
   0.168000;0.011700;,
   0.019500;0.011700;,
   0.019500;0.988300;,
   0.168000;0.988300;,
   0.168000;0.011700;,
   0.168000;0.988300;,
   0.324200;0.011700;,
   0.168000;0.011700;,
   0.168000;0.988300;,
   0.339800;0.988300;,
   0.324200;0.011700;,
   0.892600;0.238300;,
   0.697000;0.140500;,
   0.697000;0.336100;,
   0.892600;0.238300;,
   0.697000;0.140500;,
   0.697000;0.336100;,
   0.488300;0.988300;,
   0.339800;0.011700;,
   0.488300;0.011700;,
   0.011700;0.988300;,
   0.011700;0.011700;,
   0.168000;0.988300;,
   0.168000;0.988300;,
   0.011700;0.011700;,
   0.160200;0.011700;,
   0.168000;0.988300;,
   0.160200;0.011700;,
   0.347700;0.988300;,
   0.347700;0.988300;,
   0.160200;0.011700;,
   0.339800;0.011700;,
   0.347700;0.988300;,
   0.339800;0.011700;,
   0.488300;0.988300;,
   0.339800;0.011700;,
   0.347700;0.988300;,
   0.488300;0.988300;,
   0.339800;0.011700;,
   0.488300;0.988300;,
   0.488300;0.011700;,
   0.011700;0.011700;,
   0.011700;0.988300;,
   0.168000;0.988300;,
   0.011700;0.011700;,
   0.168000;0.988300;,
   0.160200;0.011700;,
   0.160200;0.011700;,
   0.168000;0.988300;,
   0.347700;0.988300;,
   0.160200;0.011700;,
   0.347700;0.988300;,
   0.339800;0.011700;,
   0.892600;0.238300;,
   0.697000;0.336100;,
   0.697000;0.140500;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_wooden_barricade_03_bone___subgroup0 }

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