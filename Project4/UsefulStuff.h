#pragma once

class UsefulStuff
{
	DirectX::XMFLOAT4X4 camera;
public:
	UsefulStuff();
	~UsefulStuff();
	void GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, UINT _indArr[36]);
	void UpdateCamera(DirectX::XMFLOAT4X4 &_camera, float const& _timer, const float _moveSpeed, const float _rotSpeed);
};

