struct INPUT_PIXEL
{
	float4 projectedCoordinate : SV_POSITION;
	float4 normals : NORMALS;
	float2 uv : UVs;
};

float4 main(INPUT_PIXEL colorFromRasterizer) : SV_TARGET
{
	return colorFromRasterizer.normals;
}