#pragma once

class UsefulStuff
{
public:
	UsefulStuff();
	~UsefulStuff();
	void GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, int _indArr[36]);
};

