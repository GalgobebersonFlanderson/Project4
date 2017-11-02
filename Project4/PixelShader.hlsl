texture2D tex : register(t0);
SamplerState texSample : register(s0);

struct INPUT_PIXEL
{
	float4 projectedCoordinate : SV_POSITION;
	float4 color : COLOR;
	float3 normals : NORMALS;
	float2 uv : UV;
};

float4 main(INPUT_PIXEL colorFromRasterizer) : SV_TARGET
{
    float4 texColor = tex.Sample(texSample, colorFromRasterizer.uv);
    if (texColor.a <= 0.5f)
        discard;
    return texColor;
}