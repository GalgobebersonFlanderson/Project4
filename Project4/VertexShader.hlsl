struct INPUT_VERTEX
{
	float4 coordinate : POSITION;
	float4 normals : NORMALS;
	float2 uv : UVs;
};

struct OUTPUT_VERTEX
{
	float4 projectedCoordinate : SV_POSITION;
	float4 normals : NORMALS;
	float2 uv : UVs;
};

cbuffer THIS_IS_VRAM : register(b0)
{
	float2 constantOffset;
	float2 padding;
};

OUTPUT_VERTEX main(INPUT_VERTEX fromVertexBuffer)
{
	OUTPUT_VERTEX sendToRasterizer = (OUTPUT_VERTEX)0;
	sendToRasterizer.projectedCoordinate.w = 1;
	sendToRasterizer.projectedCoordinate.xy = fromVertexBuffer.coordinate.xy;
	sendToRasterizer.projectedCoordinate.xy += constantOffset;
	return sendToRasterizer;
}