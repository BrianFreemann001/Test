//// A constant buffer that stores the three basic column-major matrices for composing geometry.
//cbuffer ModelViewProjectionConstantBuffer : register(b0)
//{
//	//matrix model;
//	//matrix view;
//	//matrix projection;
//    matrix wvp;
//};
//
//// Per-vertex data used as input to the vertex shader.
//struct VertexShaderInput
//{
//    float3 pos : POSITION;
//    float3 normal : NORMAL;
//    float2 uv : UV;
//};
//
//// Per-pixel color data passed through the pixel shader.
//struct PixelShaderInput
//{
//    float4 pos : SV_POSITION;
//    float4 normal : NORMAL;
//    float2 uv : UV;
//};
//
//// Simple shader to do vertex processing on the GPU.
//PixelShaderInput main(VertexShaderInput input)
//{
//	PixelShaderInput output;
//	float4 pos = float4(input.pos, 1.0f);
//
//	// Transform the vertex position into projected space.
//	//pos = mul(pos, model);
//	//pos = mul(pos, view);
//	//pos = mul(pos, projection);
//    pos = mul(pos, wvp);
//	output.pos = pos;
//
//	// Pass the color through without modification.
//    output.normal = float4(input.normal, 1.0);
//	output.uv = input.uv;
//
//	return output;
//}

cbuffer WorldViewProjection: register(b0)
{

	matrix wvp;
};

struct VS_Input
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : UV;
};
struct VS_Output
{
	float4 sv_position : SV_POSITION;
	float4 normal : NORMAL;
	float2 uv : UV;
};
VS_Output main(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	output.sv_position = mul(float4(input.position, 1.0f), wvp);
	output.normal = float4(input.normal, 1.0f);
	output.uv = input.uv;
	return output;
}