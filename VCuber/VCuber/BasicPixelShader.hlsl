Texture2D DiffuseTexture : register(t0);
SamplerState samplerState : register (s0);
// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float4 normal : COLOR;
    float2 uv : UV;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	
	return float4(DiffuseTexture.Sample(samplerState, input.uv));
}
