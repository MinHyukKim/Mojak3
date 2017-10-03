#include "MultiAnimation.vsh"


float4		vLightDiffuse		 = { 1.0f, 1.0f, 1.0f, 1.0f };   // Light Diffuse
float4		vMaterialAmbient	 : MATERIALAMBIENT = { 1.0f, 0.1f, 0.1f, 1.0f };
float4		vMaterialDiffuse	 : MATERIALDIFFUSE = { 0.8f, 0.8f, 0.8f, 1.0f };
float4		vWorldLightPos		= float4( 0.00, 500.00, -500.00, 1.00 );
float4		vWorldCameraPos		= float4( -50.00, 50.00, -50.00, 1.00 );

float4x4	g_mWorld			: WORLD;
float4x4	g_mViewProj			: VIEWPROJECTION;
texture		g_txScene;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler g_samScene =
	sampler_state
{
	Texture = <g_txScene>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4  Pos         : POSITION;
	float3  BlendWeights: BLENDWEIGHT;
	float4  BlendIndices: BLENDINDICES;
	float3  Normal      : NORMAL;
	float3  TexCoord    : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos			: POSITION;
	float4 Diffuse		: COLOR0;		//색상값
	float2 TexCoord		: TEXCOORD0;	//텍스쳐좌표
	float3 fDiffuse		: TEXCOORD1;	//없음
	float3 fViewDir		: TEXCOORD2;	//눈의 방향
	float3 fReflection	: TEXCOORD3;	//빛의 방향
};

//픽셀 셰이더
float4 PixScene( 
	float4 Diffuse		: COLOR0,
	float2 TexCoord		: TEXCOORD0,
	float3 fDiffuse		: TEXCOORD1,
	float3 fViewDir		: TEXCOORD2,
	float3 fReflection	: TEXCOORD3) : COLOR0
{
	float4 color		= saturate(Diffuse);
	float3 reflaction	= normalize(fReflection);
	float3 viewDir		= normalize(fViewDir);
	float4 specular		= float4(1.0f, 1.0f, 1.0f, 1.0f);

	if(color.a > 0)
	{
		specular = saturate(dot(reflaction, -viewDir));
		specular = pow(specular, 32.0f);	
	}

	float4 DrawColor = tex2D(g_samScene, TexCoord).rgba;
	if (DrawColor.a > 0.0f)
	{
		float intensity = (DrawColor.r * 0.3 + DrawColor.g * 0.59 + DrawColor.b * 0.11) - 0.5f;
		if (intensity < 0.0f) intensity = 0.0f;
		DrawColor.rgb = ((DrawColor.rgb * 2.0f * color.rgb) * (1.0f - intensity * 2.0f)) + (intensity * 2.0f);
	}
	//DrawColor = DrawColor * (float4(0.5f, 0.4f, 0.3f, 1.0f) + color.rgba * 2.0f / 3.0f + 0.66f);
	//DrawColor.rgb = (DrawColor.rgb + specular.rgb) * 0.5f;
	//DrawColor.rgb = (DrawColor.rgb + color.rgb + specular) / 3.0f;
	//DrawColor.rgb = (DrawColor.rgb + color.rgb) / 2.0f;
	DrawColor.a = DrawColor.a * color.a;
	//DrawColor.a = DrawColor.a * 0.9f;

	return DrawColor;
}

//버텍스 셰이더
VS_OUTPUT VertSkinning( VS_INPUT Input, uniform int nNumBones )
{
	VS_OUTPUT   Output;
	
	Output.fDiffuse		= float3(0, 0, 0);
	Output.fViewDir		= float3(0, 0, 0);
	Output.fReflection	= float3(0, 0, 0);

	float3	Pos			= 0.0f;
	float3	Normal		= 0.0f;
	float	LastWeight	= 0.0f;

	// skin VB inputs 본 매트릭스 (알 수 없음)
	VS_SKIN_INPUT vsi = { Input.Pos, Input.BlendWeights, Input.BlendIndices, Input.Normal };
	VS_SKIN_OUTPUT vso = VS_Skin( vsi, nNumBones );

	// 점의 위치
	Output.Pos = mul( float4( vso.vPos.xyz, 1.0f ), g_mViewProj ); //gl_Position = (gl_ModelViewProjectionMatrix * vec4(newVertex.xyz, 1.0));

	// 노말값
	Normal = normalize( vso.vNor );

	//빛의 방향
	float3 lightDir = normalize(vso.vPos.xyz - vWorldLightPos.xyz);

	// Shade (Ambient + etc.)
	Output.Diffuse = float4( vMaterialAmbient.rgb + saturate( dot( Normal, lightDir.rgb) ) * vMaterialDiffuse.rgb, vMaterialDiffuse.a);
	//Output.Diffuse = ceil(Output.Diffuse * 3) / 3.0f; //카툰 렌더링 연산

	// 텍스쳐 좌표
	Output.TexCoord  = Input.TexCoord.xy; //tex = vertexUV;

	

	float3 ViewDir = vso.vPos.xyz - vWorldCameraPos.xyz;
	Output.fViewDir = normalize(ViewDir);

	float3 worldNormal = normalize(Normal);

	Output.fReflection = reflect(lightDir, worldNormal);

	return Output;
}


int CurNumBones = 10;

VertexShader vsArray20[ 4 ] = { 
	compile vs_2_0 VertSkinning( 1 ),
	compile vs_2_0 VertSkinning( 2 ),
	compile vs_2_0 VertSkinning( 3 ),
	compile vs_2_0 VertSkinning( 4 ) };


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------

technique Skinning20
{
	pass p0
	{
		VertexShader = ( vsArray20[ CurNumBones ] );
		PixelShader = compile ps_2_0 PixScene();
	}
}
