#pragma once
class UsefulStuff
{
public:
	UsefulStuff();
	~UsefulStuff();
	void GenerateCubeVertsAndIndices(Vertex _vertsArr[], int _vertCount, float _depthRange, RectF _rectF, int _indArr[]);
};

