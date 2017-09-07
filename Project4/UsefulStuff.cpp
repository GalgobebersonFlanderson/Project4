#include "stdafx.h"

UsefulStuff::UsefulStuff()
{

}

UsefulStuff::~UsefulStuff()
{

}

void UsefulStuff::GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, int _indArr[36])
{
	_depthRange = fabsf(_depthRange);

	if (_rect.top > 1.0f)
		_rect.top = 1.0f;
	if (_rect.left < -1.0f)
		_rect.left = -1.0f;
	if (_rect.bottom < -1.0f)
		_rect.bottom = -1.0f;
	if (_rect.right > 1.0f)
		_rect.right = 1.0f;

	_vertsArr[0].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[0].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[1].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[1].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[2].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[2].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[3].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[3].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[4].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[4].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[5].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));		
	_vertsArr[5].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[6].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[6].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[7].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[7].normals = DirectX::XMFLOAT3(0.0f, 0.0f, _vertsArr[0].pos.z);
	_vertsArr[8].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[8].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[9].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[9].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[10].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));
	_vertsArr[10].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[11].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[11].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[12].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[12].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[13].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[13].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[14].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[14].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[15].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[15].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[16].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[16].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[17].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[17].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[18].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[18].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[19].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[19].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[20].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[20].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[21].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[21].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[22].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[22].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	_vertsArr[23].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[23].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	int indArr[36] =
	{
		0, 1, 3,
		3, 5, 0,
		7, 9, 15,
		15, 6, 7,
		8, 16, 11,
		11, 2, 8,
		23, 21, 13,
		13, 17, 23,
		14, 4, 19,
		19, 22, 14,
		10, 18, 20,
		20, 12, 10
	};

	for (int i = 0; i < 36; ++i)
	{
		unsigned int temp = indArr[i];
		if (temp == 0 || temp == 9 || temp == 16 ||
			temp == 17 || temp == 14 || temp == 10)
		{
			_vertsArr[temp].uv.x = 0.0f;
			_vertsArr[temp].uv.y = 0.0f;
		}
		else if (temp == 1 || temp == 7 || temp == 11 ||
			temp == 23 || temp == 4 || temp == 18)
		{
			_vertsArr[temp].uv.x = 1.0f;
			_vertsArr[temp].uv.y = 0.0f;
		}
		else if (temp == 3 || temp == 6 || temp == 2 ||
			temp == 21 || temp == 19 || temp == 20)
		{
			_vertsArr[temp].uv.x = 1.0f;
			_vertsArr[temp].uv.y = 1.0f;
		}
		else
		{
			_vertsArr[temp].uv.x = 0.0f;
			_vertsArr[temp].uv.y = 1.0f;
		}
	}

	memcpy(_indArr, indArr, sizeof(int) * 36);
}

