cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct INPUT_VERTEX
{
	float3 position : POSITION;
	float3 normals : NORMALS;
	float2 uv : UV;
};

struct OUTPUT_VERTEX
{
    float4 positionWS : POSITIONWS;
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float4 normals : NORMALS;
	float2 uv : UV;
};

OUTPUT_VERTEX main(INPUT_VERTEX input)
{
	float4x4 finalMat;

	OUTPUT_VERTEX output;
    output.positionWS = mul(float4(input.position, 1.0f), worldMatrix);
	output.position = float4(input.position, 1.0f);
    output.normals = float4(input.normals, 0.0f);
	finalMat = mul(worldMatrix, viewMatrix);
	finalMat = mul(finalMat, projectionMatrix);

	output.position = mul(output.position, finalMat);
    output.normals = mul(output.normals, worldMatrix);
	output.color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	output.uv = input.uv;
	return output;
}