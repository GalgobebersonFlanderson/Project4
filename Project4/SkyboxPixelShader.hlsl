textureCUBE tex : register(t0);
SamplerState texSample : register(s0);

struct INPUT_PIXEL
{
    float4 posWS : POSITIONWS;
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float3 normals : NORMALS;
    float3 uv : UV;
};

float4 main(INPUT_PIXEL input) : SV_TARGET
{
    float4 texColor = tex.Sample(texSample, input.uv);

    if (texColor.a < 0.5f)
        discard;

    return texColor;
}
