cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct INPUT_VERTEX
{
	float4 position : POSITION;
	float4 normals : NORMALS;
	float4 uv : UV;
};

struct OUTPUT_VERTEX
{
	float4 position : SV_POSITION;
	float4 normals : NORMALS;
	float4 uv : UV;
};

OUTPUT_VERTEX main(INPUT_VERTEX input)
{
	OUTPUT_VERTEX output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(input.position, viewMatrix);
	output.position = mul(input.position, projectionMatrix);

	output.normals = input.normals;
	output.uv = input.uv;
	return output;
}