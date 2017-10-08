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


Material field_build_tircho_lamp01__field_build_tircho_lamp01_dds {
 1.000000;1.000000;1.000000;0.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "field_build_tircho_lamp01.dds";
 }
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

Frame scene_field_streetlamp_01_1_light_bone02___subgroup0 {
 

 FrameTransformMatrix {
  -0.020000,0.000000,-0.000000,0.000000,-0.000000,-0.000000,0.020000,0.000000,-0.000000,0.020000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh scene_field_streetlamp_01_1_light_bone02___subgroup0 {
  186;
  69.937517;0.957923;202.285158;,
  78.324614;10.884424;208.296051;,
  80.074221;-6.897577;208.652851;,
  69.937517;0.957923;202.285158;,
  60.568314;9.158622;209.354547;,
  78.324614;10.884424;208.296051;,
  69.937517;0.957923;202.285158;,
  62.317920;-8.623377;209.711347;,
  60.568314;9.158622;209.354547;,
  69.937517;0.957923;202.285158;,
  80.074221;-6.897577;208.652851;,
  62.317920;-8.623377;209.711347;,
  72.275213;2.009223;243.214566;,
  81.497216;-6.257677;233.567360;,
  79.747610;11.524322;233.210547;,
  72.275213;2.009223;243.214566;,
  79.747610;11.524322;233.210547;,
  61.991315;9.798523;234.268954;,
  72.275213;2.009223;243.214566;,
  61.991315;9.798523;234.268954;,
  63.740813;-7.983477;234.625741;,
  72.275213;2.009223;243.214566;,
  63.740813;-7.983477;234.625741;,
  81.497216;-6.257677;233.567360;,
  80.074221;-6.897577;208.652851;,
  79.747610;11.524322;233.210547;,
  81.497216;-6.257677;233.567360;,
  78.324614;10.884424;208.296051;,
  78.324614;10.884424;208.296051;,
  61.991315;9.798523;234.268954;,
  79.747610;11.524322;233.210547;,
  60.568314;9.158622;209.354547;,
  60.568314;9.158622;209.354547;,
  63.740813;-7.983477;234.625741;,
  61.991315;9.798523;234.268954;,
  60.568314;9.158622;209.354547;,
  62.317920;-8.623377;209.711347;,
  63.740813;-7.983477;234.625741;,
  62.317920;-8.623377;209.711347;,
  81.497216;-6.257677;233.567360;,
  63.740813;-7.983477;234.625741;,
  80.074221;-6.897577;208.652851;,
  -40.257082;-19.571778;-0.000015;,
  -23.979187;-19.571778;-0.000015;,
  -25.391784;-18.159176;102.083789;,
  -38.844483;-18.159176;102.083789;,
  -23.979187;-19.571778;-0.000015;,
  -23.979187;-3.293879;-0.000015;,
  -25.391784;-4.706378;102.083789;,
  -25.391784;-18.159176;102.083789;,
  -23.979187;-3.293879;-0.000015;,
  -40.257082;-3.293879;-0.000015;,
  -38.844483;-4.706378;102.083789;,
  -25.391784;-4.706378;102.083789;,
  -40.257082;-3.293879;-0.000015;,
  -40.257082;-19.571778;-0.000015;,
  -38.844483;-18.159176;102.083789;,
  -38.844483;-4.706378;102.083789;,
  -32.027885;-11.602478;273.210214;,
  -20.850280;-22.698178;263.767091;,
  -20.850280;-0.156779;263.767219;,
  -20.850280;-0.156779;263.767219;,
  -43.391686;-0.156779;263.767219;,
  -32.027885;-11.602478;273.210214;,
  -38.844483;-18.159176;102.083789;,
  -25.391784;-18.159176;102.083789;,
  -20.850280;-22.698178;263.767091;,
  -43.391686;-22.698178;263.767091;,
  -25.391784;-18.159176;102.083789;,
  -25.391784;-4.706378;102.083789;,
  -20.850280;-0.156779;263.767219;,
  -20.850280;-22.698178;263.767091;,
  -25.391784;-4.706378;102.083789;,
  -38.844483;-4.706378;102.083789;,
  -43.391686;-0.156779;263.767219;,
  -20.850280;-0.156779;263.767219;,
  -38.844483;-4.706378;102.083789;,
  -38.844483;-18.159176;102.083789;,
  -43.391686;-22.698178;263.767091;,
  -43.391686;-0.156779;263.767219;,
  -35.961786;25.475822;-0.000015;,
  -28.274483;25.475822;-0.000015;,
  -28.941581;-5.205879;28.584976;,
  -28.941581;-5.205879;28.584976;,
  -35.294685;-5.205879;28.584976;,
  -35.961786;25.475822;-0.000015;,
  -28.274483;25.475822;-0.000015;,
  -32.118186;37.866723;-0.000015;,
  -32.118186;-5.205879;40.153581;,
  -32.118186;-5.205879;40.153581;,
  -28.941581;-5.205879;28.584976;,
  -28.274483;25.475822;-0.000015;,
  -32.118186;37.866723;-0.000015;,
  -35.961786;25.475822;-0.000015;,
  -35.294685;-5.205879;28.584976;,
  -35.294685;-5.205879;28.584976;,
  -32.118186;-5.205879;40.153581;,
  -32.118186;37.866723;-0.000015;,
  -61.608493;-35.001274;-0.000015;,
  -65.452179;-28.343875;-0.000015;,
  -38.547485;-13.580778;28.584976;,
  -38.547485;-13.580778;28.584976;,
  -35.370986;-19.082774;28.584976;,
  -61.608493;-35.001274;-0.000015;,
  -65.452179;-28.343875;-0.000015;,
  -74.261184;-37.868077;-0.000015;,
  -36.959184;-16.331776;40.153581;,
  -36.959184;-16.331776;40.153581;,
  -38.547485;-13.580778;28.584976;,
  -65.452179;-28.343875;-0.000015;,
  -74.261184;-37.868077;-0.000015;,
  -61.608493;-35.001274;-0.000015;,
  -35.370986;-19.082774;28.584976;,
  -35.370986;-19.082774;28.584976;,
  -36.959184;-16.331776;40.153581;,
  -74.261184;-37.868077;-0.000015;,
  0.983719;-28.156877;-0.000015;,
  -2.859985;-34.814275;-0.000015;,
  -29.097581;-18.895779;28.584976;,
  -29.097581;-18.895779;28.584976;,
  -25.920982;-13.393778;28.584976;,
  0.983719;-28.156877;-0.000015;,
  -2.859985;-34.814275;-0.000015;,
  9.792717;-37.681075;-0.000015;,
  -27.509286;-16.144776;40.153581;,
  -27.509286;-16.144776;40.153581;,
  -29.097581;-18.895779;28.584976;,
  -2.859985;-34.814275;-0.000015;,
  9.792717;-37.681075;-0.000015;,
  0.983719;-28.156877;-0.000015;,
  -25.920982;-13.393778;28.584976;,
  -25.920982;-13.393778;28.584976;,
  -27.509286;-16.144776;40.153581;,
  9.792717;-37.681075;-0.000015;,
  -32.027885;-11.602478;273.210214;,
  -43.391686;-0.156779;263.767219;,
  -43.391686;-22.698178;263.767091;,
  -43.391686;-22.698178;263.767091;,
  -20.850280;-22.698178;263.767091;,
  -32.027885;-11.602478;273.210214;,
  -81.497376;-3.846779;225.870976;,
  -79.506989;-3.846779;214.582387;,
  79.720019;-3.846979;242.658278;,
  77.729517;-3.846979;253.947290;,
  -79.506989;-3.846779;214.582387;,
  -79.506989;8.698922;214.582490;,
  79.720115;8.699023;242.658278;,
  79.720115;8.699023;242.658278;,
  79.720019;-3.846979;242.658278;,
  -79.506989;-3.846779;214.582387;,
  -79.506989;8.698922;214.582490;,
  -81.497376;8.698922;225.870976;,
  77.729517;8.699023;253.947290;,
  79.720115;8.699023;242.658278;,
  -81.497376;8.698922;225.870976;,
  -81.497376;-3.846779;225.870976;,
  77.729517;-3.846979;253.947290;,
  77.729517;8.699023;253.947290;,
  -79.506989;-3.846779;214.582387;,
  -81.497376;-3.846779;225.870976;,
  -81.497376;8.698922;225.870976;,
  -79.506989;8.698922;214.582490;,
  -79.506989;-3.846779;214.582387;,
  -81.497376;8.698922;225.870976;,
  77.729517;-3.846979;253.947290;,
  79.720019;-3.846979;242.658278;,
  77.729517;8.699023;253.947290;,
  79.720019;-3.846979;242.658278;,
  79.720115;8.699023;242.658278;,
  77.729517;8.699023;253.947290;,
  -69.492083;2.426021;225.488486;,
  -77.303085;-1.812379;221.846093;,
  -39.118682;-14.780178;146.826778;,
  -39.118682;-14.780178;146.826778;,
  -31.307280;-10.541578;150.469389;,
  -69.492083;2.426021;225.488486;,
  -77.303085;-1.812379;221.846093;,
  -77.303085;6.664422;221.846093;,
  -39.118682;-6.303079;146.826778;,
  -39.118682;-14.780178;146.826778;,
  -77.303085;6.664422;221.846093;,
  -69.492083;2.426021;225.488486;,
  -31.307280;-10.541578;150.469389;,
  -31.307280;-10.541578;150.469389;,
  -39.118682;-6.303079;146.826778;,
  -77.303085;6.664422;221.846093;;
  72;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;15,16,17;,
  3;18,19,20;,
  3;21,22,23;,
  3;24,25,26;,
  3;24,27,25;,
  3;28,29,30;,
  3;28,31,29;,
  3;32,33,34;,
  3;35,36,37;,
  3;38,39,40;,
  3;38,41,39;,
  3;42,43,44;,
  3;44,45,42;,
  3;46,47,48;,
  3;48,49,46;,
  3;50,51,52;,
  3;52,53,50;,
  3;54,55,56;,
  3;56,57,54;,
  3;58,59,60;,
  3;61,62,63;,
  3;64,65,66;,
  3;66,67,64;,
  3;68,69,70;,
  3;70,71,68;,
  3;72,73,74;,
  3;74,75,72;,
  3;76,77,78;,
  3;78,79,76;,
  3;80,81,82;,
  3;83,84,85;,
  3;86,87,88;,
  3;89,90,91;,
  3;92,93,94;,
  3;95,96,97;,
  3;98,99,100;,
  3;101,102,103;,
  3;104,105,106;,
  3;107,108,109;,
  3;110,111,112;,
  3;113,114,115;,
  3;116,117,118;,
  3;119,120,121;,
  3;122,123,124;,
  3;125,126,127;,
  3;128,129,130;,
  3;131,132,133;,
  3;134,135,136;,
  3;137,138,139;,
  3;140,141,142;,
  3;142,143,140;,
  3;144,145,146;,
  3;147,148,149;,
  3;150,151,152;,
  3;152,153,150;,
  3;154,155,156;,
  3;156,157,154;,
  3;158,159,160;,
  3;161,162,163;,
  3;164,165,166;,
  3;167,168,169;,
  3;170,171,172;,
  3;173,174,175;,
  3;176,177,178;,
  3;178,179,176;,
  3;180,181,182;,
  3;183,184,185;;

  MeshNormals {
   186;
   0.552307;0.037633;-0.832791;,
   0.552307;0.037633;-0.832791;,
   0.552307;0.037633;-0.832791;,
   -0.104436;0.578223;-0.809167;,
   -0.104436;0.578223;-0.809167;,
   -0.104436;0.578223;-0.809167;,
   -0.643369;-0.078582;-0.761512;,
   -0.643369;-0.078582;-0.761512;,
   -0.643369;-0.078582;-0.761512;,
   0.013376;-0.619176;-0.785138;,
   0.013376;-0.619176;-0.785138;,
   0.013376;-0.619176;-0.785138;,
   0.756448;0.087434;0.648183;,
   0.756448;0.087434;0.648183;,
   0.756448;0.087434;0.648183;,
   -0.031187;0.735767;0.676516;,
   -0.031187;0.735767;0.676516;,
   -0.031187;0.735767;0.676516;,
   -0.677526;-0.051938;0.733662;,
   -0.677526;-0.051938;0.733662;,
   -0.677526;-0.051938;0.733662;,
   0.110104;-0.700274;0.705332;,
   0.110104;-0.700274;0.705332;,
   0.110104;-0.700274;0.705332;,
   0.993562;0.096570;-0.059228;,
   0.993562;0.096570;-0.059228;,
   0.993562;0.096570;-0.059228;,
   0.993562;0.096570;-0.059228;,
   -0.097897;0.994996;-0.019964;,
   -0.097897;0.994996;-0.019964;,
   -0.097897;0.994996;-0.019964;,
   -0.097898;0.994996;-0.019964;,
   -0.993563;-0.096564;0.059228;,
   -0.993563;-0.096564;0.059228;,
   -0.993563;-0.096564;0.059228;,
   -0.993563;-0.096570;0.059224;,
   -0.993563;-0.096570;0.059224;,
   -0.993563;-0.096570;0.059224;,
   0.097897;-0.994996;0.019964;,
   0.097897;-0.994996;0.019964;,
   0.097897;-0.994996;0.019964;,
   0.097897;-0.994996;0.019964;,
   0.000000;-0.999904;0.013836;,
   0.000000;-0.999904;0.013836;,
   0.000000;-0.999904;0.013836;,
   0.000000;-0.999904;0.013836;,
   0.999904;0.000000;0.013836;,
   0.999904;0.000000;0.013836;,
   0.999904;0.000000;0.013836;,
   0.999904;0.000000;0.013836;,
   0.000000;0.999904;0.013835;,
   0.000000;0.999904;0.013835;,
   0.000000;0.999904;0.013835;,
   0.000000;0.999904;0.013835;,
   -0.999904;0.000000;0.013836;,
   -0.999904;0.000000;0.013836;,
   -0.999904;0.000000;0.013836;,
   -0.999904;0.000000;0.013836;,
   0.645348;-0.000004;0.763889;,
   0.645348;-0.000004;0.763889;,
   0.645348;-0.000004;0.763889;,
   0.000000;0.636395;0.771364;,
   0.000000;0.636395;0.771364;,
   0.000000;0.636395;0.771364;,
   -0.000000;-0.999606;-0.028062;,
   -0.000000;-0.999606;-0.028062;,
   -0.000000;-0.999606;-0.028062;,
   -0.000000;-0.999606;-0.028062;,
   0.999606;-0.000000;-0.028078;,
   0.999606;-0.000000;-0.028078;,
   0.999606;-0.000000;-0.028078;,
   0.999606;-0.000000;-0.028078;,
   -0.000000;0.999604;-0.028128;,
   -0.000000;0.999604;-0.028128;,
   -0.000000;0.999604;-0.028128;,
   -0.000000;0.999604;-0.028128;,
   -0.999605;-0.000000;-0.028113;,
   -0.999605;-0.000000;-0.028113;,
   -0.999605;-0.000000;-0.028113;,
   -0.999605;-0.000000;-0.028113;,
   -0.000000;-0.681665;-0.731664;,
   -0.000000;-0.681665;-0.731664;,
   -0.000000;-0.681665;-0.731664;,
   -0.000000;-0.681664;-0.731665;,
   -0.000000;-0.681664;-0.731665;,
   -0.000000;-0.681664;-0.731665;,
   0.910238;0.282359;0.302886;,
   0.910238;0.282359;0.302886;,
   0.910238;0.282359;0.302886;,
   0.940640;0.220186;0.258290;,
   0.940640;0.220186;0.258290;,
   0.940640;0.220186;0.258290;,
   -0.904187;0.280475;0.322148;,
   -0.904187;0.280475;0.322148;,
   -0.904187;0.280475;0.322148;,
   -0.936210;0.239643;0.257064;,
   -0.936210;0.239643;0.257064;,
   -0.936210;0.239643;0.257064;,
   0.590338;0.340833;-0.731665;,
   0.590338;0.340833;-0.731665;,
   0.590338;0.340833;-0.731665;,
   0.590344;0.340827;-0.731664;,
   0.590344;0.340827;-0.731664;,
   0.590344;0.340827;-0.731664;,
   -0.699649;0.647110;0.302886;,
   -0.699649;0.647110;0.302886;,
   -0.699649;0.647110;0.302886;,
   -0.661005;0.704528;0.258288;,
   -0.661005;0.704528;0.258288;,
   -0.661005;0.704528;0.258288;,
   0.209195;-0.923287;0.322148;,
   0.209195;-0.923287;0.322148;,
   0.209195;-0.923287;0.322148;,
   0.260564;-0.930604;0.257067;,
   0.260564;-0.930604;0.257067;,
   0.260564;-0.930604;0.257067;,
   -0.590337;0.340837;-0.731664;,
   -0.590337;0.340837;-0.731664;,
   -0.590337;0.340837;-0.731664;,
   -0.590338;0.340833;-0.731665;,
   -0.590338;0.340833;-0.731665;,
   -0.590338;0.340833;-0.731665;,
   -0.210596;-0.929470;0.302879;,
   -0.210596;-0.929470;0.302879;,
   -0.210596;-0.929470;0.302879;,
   -0.279632;-0.924713;0.258287;,
   -0.279632;-0.924713;0.258287;,
   -0.279632;-0.924713;0.258287;,
   0.694994;0.642805;0.322157;,
   0.694994;0.642805;0.322157;,
   0.694994;0.642805;0.322157;,
   0.675645;0.690955;0.257070;,
   0.675645;0.690955;0.257070;,
   0.675645;0.690955;0.257070;,
   -0.639114;-0.000004;0.769112;,
   -0.639114;-0.000004;0.769112;,
   -0.639114;-0.000004;0.769112;,
   0.000000;-0.648117;0.761540;,
   0.000000;-0.648117;0.761540;,
   0.000000;-0.648117;0.761540;,
   -0.000001;-1.000000;0.000000;,
   -0.000001;-1.000000;0.000000;,
   -0.000001;-1.000000;0.000000;,
   -0.000001;-1.000000;0.000000;,
   0.173647;0.000008;-0.984808;,
   0.173647;0.000008;-0.984808;,
   0.173647;0.000008;-0.984808;,
   0.173647;-0.000001;-0.984808;,
   0.173647;-0.000001;-0.984808;,
   0.173647;-0.000001;-0.984808;,
   -0.000001;1.000000;-0.000000;,
   -0.000001;1.000000;-0.000000;,
   -0.000001;1.000000;-0.000000;,
   -0.000001;1.000000;-0.000000;,
   -0.173650;0.000000;0.984807;,
   -0.173650;0.000000;0.984807;,
   -0.173650;0.000000;0.984807;,
   -0.173650;0.000000;0.984807;,
   -0.984809;-0.000000;-0.173639;,
   -0.984809;-0.000000;-0.173639;,
   -0.984809;-0.000000;-0.173639;,
   -0.984809;0.000001;-0.173641;,
   -0.984809;0.000001;-0.173641;,
   -0.984809;0.000001;-0.173641;,
   0.984809;0.000000;0.173644;,
   0.984809;0.000000;0.173644;,
   0.984809;0.000000;0.173644;,
   0.984807;-0.000008;0.173652;,
   0.984807;-0.000008;0.173652;,
   0.984807;-0.000008;0.173652;,
   0.331182;-0.886964;0.321889;,
   0.331182;-0.886964;0.321889;,
   0.331182;-0.886964;0.321889;,
   0.331179;-0.886966;0.321889;,
   0.331179;-0.886966;0.321889;,
   0.331179;-0.886966;0.321889;,
   -0.891198;-0.000000;-0.453615;,
   -0.891198;-0.000000;-0.453615;,
   -0.891198;-0.000000;-0.453615;,
   -0.891198;-0.000000;-0.453615;,
   0.448592;0.890636;0.074381;,
   0.448592;0.890636;0.074381;,
   0.448592;0.890636;0.074381;,
   0.448583;0.890641;0.074374;,
   0.448583;0.890641;0.074374;,
   0.448583;0.890641;0.074374;;
   72;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;24,27,25;,
   3;28,29,30;,
   3;28,31,29;,
   3;32,33,34;,
   3;35,36,37;,
   3;38,39,40;,
   3;38,41,39;,
   3;42,43,44;,
   3;44,45,42;,
   3;46,47,48;,
   3;48,49,46;,
   3;50,51,52;,
   3;52,53,50;,
   3;54,55,56;,
   3;56,57,54;,
   3;58,59,60;,
   3;61,62,63;,
   3;64,65,66;,
   3;66,67,64;,
   3;68,69,70;,
   3;70,71,68;,
   3;72,73,74;,
   3;74,75,72;,
   3;76,77,78;,
   3;78,79,76;,
   3;80,81,82;,
   3;83,84,85;,
   3;86,87,88;,
   3;89,90,91;,
   3;92,93,94;,
   3;95,96,97;,
   3;98,99,100;,
   3;101,102,103;,
   3;104,105,106;,
   3;107,108,109;,
   3;110,111,112;,
   3;113,114,115;,
   3;116,117,118;,
   3;119,120,121;,
   3;122,123,124;,
   3;125,126,127;,
   3;128,129,130;,
   3;131,132,133;,
   3;134,135,136;,
   3;137,138,139;,
   3;140,141,142;,
   3;142,143,140;,
   3;144,145,146;,
   3;147,148,149;,
   3;150,151,152;,
   3;152,153,150;,
   3;154,155,156;,
   3;156,157,154;,
   3;158,159,160;,
   3;161,162,163;,
   3;164,165,166;,
   3;167,168,169;,
   3;170,171,172;,
   3;173,174,175;,
   3;176,177,178;,
   3;178,179,176;,
   3;180,181,182;,
   3;183,184,185;;
  }

  MeshMaterialList {
   2;
   72;
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1;
   { field_build_tircho_lamp01__field_build_tircho_lamp01_dds }
   { field_object_01__field_object_01_dds }
  }

  MeshTextureCoords c1 {
   186;
   0.416900;0.757300;,
   0.365800;0.713400;,
   0.365800;0.797300;,
   0.416900;0.757300;,
   0.365800;0.797300;,
   0.365800;0.713400;,
   0.416900;0.757300;,
   0.365800;0.713400;,
   0.365800;0.797300;,
   0.416900;0.757300;,
   0.365800;0.797300;,
   0.365800;0.713400;,
   0.320100;0.754200;,
   0.392000;0.796500;,
   0.392000;0.713300;,
   0.320100;0.754200;,
   0.392000;0.713300;,
   0.392000;0.796500;,
   0.320100;0.754200;,
   0.392000;0.796500;,
   0.392000;0.713300;,
   0.320100;0.754200;,
   0.392000;0.713300;,
   0.392000;0.796500;,
   0.007800;0.242200;,
   0.523400;0.007800;,
   0.523400;0.242200;,
   0.007800;0.007800;,
   0.007800;0.007800;,
   0.523400;0.242200;,
   0.523400;0.007800;,
   0.007800;0.242200;,
   0.007800;0.242200;,
   0.523400;0.007800;,
   0.523400;0.242200;,
   0.007800;0.242200;,
   0.007800;0.007800;,
   0.523400;0.007800;,
   0.007800;0.007800;,
   0.523400;0.242200;,
   0.523400;0.007800;,
   0.007800;0.242200;,
   0.498600;0.802500;,
   0.498600;0.709200;,
   0.210000;0.709200;,
   0.210000;0.802500;,
   0.498600;0.709200;,
   0.498600;0.802500;,
   0.210000;0.802500;,
   0.210000;0.709200;,
   0.498600;0.802500;,
   0.498600;0.709200;,
   0.210000;0.709200;,
   0.210000;0.802500;,
   0.498600;0.709200;,
   0.498600;0.802500;,
   0.210000;0.802500;,
   0.210000;0.709200;,
   0.005100;0.756900;,
   0.029800;0.802200;,
   0.029800;0.709200;,
   0.029800;0.709200;,
   0.029800;0.802200;,
   0.005100;0.756900;,
   0.511800;0.802500;,
   0.511800;0.709200;,
   0.029800;0.709200;,
   0.029800;0.802200;,
   0.511800;0.709200;,
   0.511800;0.802500;,
   0.029800;0.802200;,
   0.029800;0.709200;,
   0.511800;0.802500;,
   0.511800;0.709200;,
   0.029800;0.709200;,
   0.029800;0.802200;,
   0.511800;0.709200;,
   0.511800;0.802500;,
   0.029800;0.802200;,
   0.029800;0.709200;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.167100;0.802500;,
   0.167100;0.802500;,
   0.167100;0.709200;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.167100;0.802500;,
   0.167100;0.802500;,
   0.167100;0.709200;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.167100;0.802500;,
   0.167100;0.802500;,
   0.167100;0.709200;,
   0.366700;0.709200;,
   0.366700;0.802500;,
   0.366700;0.709200;,
   0.167100;0.709200;,
   0.167100;0.709200;,
   0.167100;0.802500;,
   0.366700;0.802500;,
   0.005100;0.756900;,
   0.029800;0.802200;,
   0.029800;0.709200;,
   0.029800;0.709200;,
   0.029800;0.802200;,
   0.005100;0.756900;,
   0.489300;0.802500;,
   0.489300;0.709200;,
   0.130500;0.709200;,
   0.130600;0.802200;,
   0.489300;0.709200;,
   0.489300;0.802500;,
   0.130600;0.802200;,
   0.130600;0.802200;,
   0.130500;0.709200;,
   0.489300;0.709200;,
   0.489300;0.802500;,
   0.489300;0.709200;,
   0.130500;0.709200;,
   0.130600;0.802200;,
   0.489300;0.709200;,
   0.489300;0.802500;,
   0.130600;0.802200;,
   0.130500;0.709200;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.490200;0.732500;,
   0.370700;0.802500;,
   0.370700;0.709200;,
   0.165000;0.709200;,
   0.165000;0.709200;,
   0.165100;0.802200;,
   0.370700;0.802500;,
   0.370700;0.709200;,
   0.370700;0.802500;,
   0.165100;0.802200;,
   0.165000;0.709200;,
   0.370700;0.709100;,
   0.370700;0.802300;,
   0.165000;0.802300;,
   0.165000;0.802300;,
   0.165100;0.709400;,
   0.370700;0.709100;;
  }
 }
}

AnimTicksPerSecond  {
 4800;
}

AnimationSet Anim1 {
 

 Animation {
  
  { scene_field_streetlamp_01_1_light_bone02___subgroup0 }

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