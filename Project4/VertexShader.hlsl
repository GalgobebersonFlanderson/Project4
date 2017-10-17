cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct INPUT_VERTEX
{
	float3 position : POSITION;
	float4 color : COLOR;
	float3 normals : NORMALS;
	float2 uv : UV;
};

struct OUTPUT_VERTEX
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float3 normals : NORMALS;
	float2 uv : UV;
};

OUTPUT_VERTEX main(INPUT_VERTEX input)
{
	float4x4 finalMat;

	OUTPUT_VERTEX output;
	output.position = float4(input.position, 1.0f);
	finalMat = mul(worldMatrix, viewMatrix);
	finalMat = mul(finalMat, projectionMatrix);

	output.position = mul(output.position, finalMat);
	output.color = input.color;
	output.normals = input.normals;
	output.uv = input.uv;
	return output;
}