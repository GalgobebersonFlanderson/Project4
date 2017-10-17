#include "stdafx.h"

UsefulStuff::UsefulStuff()
{

}

UsefulStuff::~UsefulStuff()
{

}

void UsefulStuff::GenerateCubeVertsAndIndices(Vertex _vertsArr[24], float _depthRange, RectF _rect, UINT _indArr[36])
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

	//Position
	_vertsArr[0].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[1].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[2].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[3].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[4].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[5].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));		
	_vertsArr[6].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[7].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[8].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[9].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[10].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, -(_depthRange));
	_vertsArr[11].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[12].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[13].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[14].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[15].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[16].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[17].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[18].pos = DirectX::XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[19].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[20].pos = DirectX::XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[21].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[22].pos = DirectX::XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[23].pos = DirectX::XMFLOAT3(_rect.left, _rect.top, _depthRange);

	//Index
	UINT indArr[36] =
	{
		0, 1, 3,
		3, 5, 0,	//Front Face
		7, 15, 9,
		15, 7, 6,	//Left Face
		8, 16, 11,
		11, 2, 8,	//Top Face
		23, 21, 13,
		13, 17, 23,	//Back Face
		14, 4, 19,
		19, 22, 14,	//Bottom Face
		10, 18, 20,
		20, 12, 10	//Right Face
	};

	unsigned int temp, i;
	
	//Color
	for (i = 0; i < 36; ++i)
	{
		temp = indArr[i];

		if (temp == 0 || temp == 1 || temp == 3 || temp == 5)
			_vertsArr[temp].color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		else if (temp == 7 || temp == 15 || temp == 9 || temp == 6)
			_vertsArr[temp].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		else if (temp == 8 || temp == 16 || temp == 11 || temp == 2)
			_vertsArr[temp].color = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		else if (temp == 23 || temp == 21 || temp == 13 || temp == 17)
			_vertsArr[temp].color = DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
		else if (temp == 14 || temp == 4 || temp == 19 || temp == 22)
			_vertsArr[temp].color = DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
		else if (temp == 10 || temp == 18 || temp == 20 || temp == 12)
			_vertsArr[temp].color = DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	}

	//Normal
	for (i = 0; i < 36; ++i)
	{
		temp = indArr[i];

		if (temp == 0 || temp == 1 || temp == 3 || temp == 5)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
		else if (temp == 7 || temp == 15 || temp == 9 || temp == 6)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f);
		else if (temp == 8 || temp == 16 || temp == 11 || temp == 2)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
		else if (temp == 23 || temp == 21 || temp == 13 || temp == 17)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
		else if (temp == 14 || temp == 4 || temp == 19 || temp == 22)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
		else if (temp == 10 || temp == 18 || temp == 20 || temp == 12)
			_vertsArr[temp].normals = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	}

	//UV
	for (i = 0; i < 36; ++i)
	{
		temp = indArr[i];
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

void UsefulStuff::UpdateCamera(DirectX::XMFLOAT4X4 &_camera, float const &_timer, const float _moveSpeed, const float _rotSpeed)
{
	DirectX::XMMATRIX translation = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX temp_cam = DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&_camera));

	//Move camera up
	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = DirectX::XMMatrixTranslation(0.0f, _moveSpeed * _timer, 0.0f);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Move camera down
	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = DirectX::XMMatrixTranslation(0.0f, -_moveSpeed * _timer, 0.0f);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Move camera left
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = DirectX::XMMatrixTranslation(-_moveSpeed * _timer, 0.0f, 0.0f);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Move camera right
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = DirectX::XMMatrixTranslation(_moveSpeed * _timer, 0.0f, 0.0f);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Move camera forward
	if ((GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('W')) || (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_UP)))
	{
		translation = DirectX::XMMatrixTranslation(0.0f, 0.0f, _moveSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Move camera back
	if ((GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('S')) || (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_DOWN)))
	{
		translation = DirectX::XMMatrixTranslation(0.0f, 0.0f, -_moveSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Rotate camera left
	if ((GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('A')) || (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LEFT)))
	{
		translation = DirectX::XMMatrixRotationY(-_rotSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Rotate camera right
	if ((GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('D')) || (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_RIGHT)))
	{
		translation = DirectX::XMMatrixRotationY(_rotSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Rotate camera up
	if ((GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('W')) || (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_UP)))
	{
		translation = DirectX::XMMatrixRotationX(-_rotSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}
	//Rotate camera down
	if ((GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('S')) || (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_DOWN)))
	{
		translation = DirectX::XMMatrixRotationX(_rotSpeed * _timer);
		temp_cam = DirectX::XMMatrixMultiply(translation, temp_cam);
	}

	temp_cam = DirectX::XMMatrixInverse(nullptr, temp_cam);
	DirectX::XMStoreFloat4x4(&_camera, temp_cam);
}

