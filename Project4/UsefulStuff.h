#pragma once

using namespace DirectX;

class UsefulStuff
{
	DirectX::XMFLOAT4X4 camera;
	POINT cursorPrev = POINT();
public:
	UsefulStuff();
	~UsefulStuff();
	void GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, UINT _indArr[36]);
	void UpdateCamera(DirectX::XMFLOAT4X4 &_camera, float const& _timer, const float _moveSpeed, const float _rotSpeed);
	bool LoadOBJFile(const char *_path, std::vector<VertexOBJ> &_outVert, std::vector<unsigned int> &_outInd);
};

