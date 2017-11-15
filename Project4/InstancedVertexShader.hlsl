cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix[4];
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct INPUT_VERTEX
{
    float3 position : POSITION;
    float4 color : COLOR;
    float3 normals : NORMALS;
    float2 uv : UV;
    uint instanceId : SV_InstanceID;
};

struct OUTPUT_VERTEX
{
    float4 positionWS : POSITIONWS;
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 normals : NORMALS;
    float2 uv : UV;
    uint instanceId : SV_InstanceID;
};

OUTPUT_VERTEX main(INPUT_VERTEX input)
{
    float4x4 finalMat;

    OUTPUT_VERTEX output;
    output.positionWS = mul(float4(input.position, 1.0f), worldMatrix[input.instanceId]);
    output.position = float4(input.position, 1.0f);
    output.normals = float4(input.normals, 0.0f);
    finalMat = mul(worldMatrix[input.instanceId], viewMatrix);
    finalMat = mul(finalMat, projectionMatrix);

    output.position = mul(output.position, finalMat);
    output.normals = mul(output.normals, worldMatrix[input.instanceId]);
    output.color = input.color;
    output.uv = input.uv;
    output.instanceId = input.instanceId;
    return output;
}