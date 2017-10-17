struct INPUT_PIXEL
{
	float4 projectedCoordinate : SV_POSITION;
	float4 color : COLOR;
	float3 normals : NORMALS;
	float2 uv : UV;
};

float4 main(INPUT_PIXEL colorFromRasterizer) : SV_TARGET
{
	return colorFromRasterizer.color;
}