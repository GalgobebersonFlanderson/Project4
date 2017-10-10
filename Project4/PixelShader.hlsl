struct INPUT_PIXEL
{
	float4 projectedCoordinate : SV_POSITION;
	float3 normals : NORMALS;
	float2 uv : UV;
};

float3 main(INPUT_PIXEL colorFromRasterizer) : SV_TARGET
{
	colorFromRasterizer.normals = float3(1.0f, 0.0f, 1.0f);
	return colorFromRasterizer.normals;
}