#pragma once

class UsefulStuff
{
public:
	UsefulStuff();
	~UsefulStuff();
	void GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, UINT _indArr[36]);
};

