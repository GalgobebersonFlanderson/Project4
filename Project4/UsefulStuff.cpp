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
	_vertsArr[0].pos = XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[1].pos = XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[2].pos = XMFLOAT3(_rect.right, _rect.top, -(_depthRange));	
	_vertsArr[3].pos = XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[4].pos = XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[5].pos = XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));		
	_vertsArr[6].pos = XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[7].pos = XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[8].pos = XMFLOAT3(_rect.left, _rect.top, -(_depthRange));
	_vertsArr[9].pos = XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[10].pos = XMFLOAT3(_rect.right, _rect.top, -(_depthRange));
	_vertsArr[11].pos = XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[12].pos = XMFLOAT3(_rect.right, _rect.bottom, -(_depthRange));
	_vertsArr[13].pos = XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[14].pos = XMFLOAT3(_rect.left, _rect.bottom, -(_depthRange));
	_vertsArr[15].pos = XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[16].pos = XMFLOAT3(_rect.left, _rect.top, _depthRange);
	_vertsArr[17].pos = XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[18].pos = XMFLOAT3(_rect.right, _rect.top, _depthRange);
	_vertsArr[19].pos = XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[20].pos = XMFLOAT3(_rect.right, _rect.bottom, _depthRange);
	_vertsArr[21].pos = XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[22].pos = XMFLOAT3(_rect.left, _rect.bottom, _depthRange);
	_vertsArr[23].pos = XMFLOAT3(_rect.left, _rect.top, _depthRange);

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
			_vertsArr[temp].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		else if (temp == 7 || temp == 15 || temp == 9 || temp == 6)
			_vertsArr[temp].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		else if (temp == 8 || temp == 16 || temp == 11 || temp == 2)
			_vertsArr[temp].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		else if (temp == 23 || temp == 21 || temp == 13 || temp == 17)
			_vertsArr[temp].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
		else if (temp == 14 || temp == 4 || temp == 19 || temp == 22)
			_vertsArr[temp].color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);
		else if (temp == 10 || temp == 18 || temp == 20 || temp == 12)
			_vertsArr[temp].color = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	}

	//Normal
	for (i = 0; i < 36; ++i)
	{
		temp = indArr[i];

		if (temp == 0 || temp == 1 || temp == 3 || temp == 5)
			_vertsArr[temp].normals = XMFLOAT3(0.0f, 0.0f, -1.0f);	//Front Face
		else if (temp == 7 || temp == 15 || temp == 9 || temp == 6)
			_vertsArr[temp].normals = XMFLOAT3(-1.0f, 0.0f, 0.0f);	//Left Face
		else if (temp == 8 || temp == 16 || temp == 11 || temp == 2)
			_vertsArr[temp].normals = XMFLOAT3(0.0f, 1.0f, 0.0f);	//Top Face
		else if (temp == 23 || temp == 21 || temp == 13 || temp == 17)
			_vertsArr[temp].normals = XMFLOAT3(0.0f, 0.0f, 1.0f);	//Back Face
		else if (temp == 14 || temp == 4 || temp == 19 || temp == 22)
			_vertsArr[temp].normals = XMFLOAT3(0.0f, -1.0f, 0.0f);	//Bottom Face
		else if (temp == 10 || temp == 18 || temp == 20 || temp == 12)
			_vertsArr[temp].normals = XMFLOAT3(1.0f, 0.0f, 0.0f);	//Right Face
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

void UsefulStuff::UpdateCamera(XMFLOAT4X4 &_camera, float const &_timer, const float _moveSpeed, const float _rotSpeed)
{
	POINT cursorCurr;
	XMMATRIX translation = XMMatrixIdentity();
	XMFLOAT4X4 temp_cam = _camera;

	//Move camera up
	if ((GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = XMMatrixTranslation(0.0f, _moveSpeed * _timer, 0.0f);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}
	//Move camera down
	if ((GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = XMMatrixTranslation(0.0f, -_moveSpeed * _timer, 0.0f);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}
	//Move camera left
	if ((GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = XMMatrixTranslation(-_moveSpeed * _timer, 0.0f, 0.0f);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}
	//Move camera right
	if ((GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT)) && !GetAsyncKeyState(VK_LSHIFT))
	{
		translation = XMMatrixTranslation(_moveSpeed * _timer, 0.0f, 0.0f);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}
	//Move camera forward
	if ((GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('W')) || (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_UP)))
	{
		translation = XMMatrixTranslation(0.0f, 0.0f, _moveSpeed * _timer);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}
	//Move camera back
	if ((GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState('S')) || (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_DOWN)))
	{
		translation = XMMatrixTranslation(0.0f, 0.0f, -_moveSpeed * _timer);
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(translation, XMLoadFloat4x4(&temp_cam)));
	}

	//Rotation using mouse
	GetCursorPos(&cursorCurr);

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		float dx = (float)cursorCurr.x - cursorPrev.x;
		float dy = (float)cursorCurr.y - cursorPrev.y;

		XMFLOAT4 pos = XMFLOAT4(temp_cam._41, temp_cam._42, temp_cam._43, temp_cam._44);

		temp_cam._41 = 0;
		temp_cam._42 = 0;
		temp_cam._43 = 0;

		XMMATRIX rotX = XMMatrixRotationX(dy * _rotSpeed * _timer);
		XMMATRIX rotY = XMMatrixRotationY(dx * _rotSpeed * _timer);

		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(rotX, XMLoadFloat4x4(&temp_cam)));
		XMStoreFloat4x4(&temp_cam, XMMatrixMultiply(XMLoadFloat4x4(&temp_cam), rotY));

		temp_cam._41 = pos.x;
		temp_cam._42 = pos.y;
		temp_cam._43 = pos.z;
	}

	cursorPrev = cursorCurr;

	XMStoreFloat4x4(&_camera, XMLoadFloat4x4(&temp_cam));
}

XMMATRIX UsefulStuff::Translate(XMFLOAT3 _xyz, float _delta, XMMATRIX _mat)
{
	if (_delta != 0)
		_mat *= XMMatrixTranspose(XMMatrixTranslation(_xyz.x * _delta, _xyz.y * _delta, _xyz.z * _delta));
	else
		_mat *= XMMatrixTranspose(XMMatrixTranslation(_xyz.x, _xyz.y, _xyz.z));

	return _mat;
}

XMMATRIX UsefulStuff::Scale(XMFLOAT3 _xyz, float _delta, XMMATRIX _mat)
{
	if (_delta != 0)
		_mat *= XMMatrixScaling(_xyz.x * _delta, _xyz.y * _delta, _xyz.z * _delta);
	else
		_mat *= XMMatrixScaling(_xyz.x, _xyz.y, _xyz.z);

	return _mat;
}

XMMATRIX UsefulStuff::Rotate(XMFLOAT3 _xyz, float _delta, XMMATRIX _mat)
{
	if (_delta != 0)
	{
		_mat *= XMMatrixRotationX(_xyz.x * _delta);
		_mat *= XMMatrixRotationY(_xyz.y * _delta);
		_mat *= XMMatrixRotationZ(_xyz.z * _delta);
	}

	else
	{
		_mat *= XMMatrixRotationX(_xyz.x);
		_mat *= XMMatrixRotationY(_xyz.y);
		_mat *= XMMatrixRotationZ(_xyz.z);
	}

	return _mat;
}

bool UsefulStuff::LoadOBJFile(const char *_path, std::vector<VertexOBJ> &_outVert, std::vector<unsigned int> &_outInd)
{
	std::vector<unsigned int> vInds, uvInds, nInds;
	std::vector<XMFLOAT3> temp_verts;
	std::vector<XMFLOAT2> temp_uvs;
	std::vector<XMFLOAT3> temp_normals;

	FILE *file = nullptr;
	fopen_s(&file, _path, "r");

	if (file == NULL)
	{
		printf("Cannot open file.\n");
		return false;
	}

	while (true)
	{
		char lineHeader[128];
		int res = fscanf_s(file, "%s", lineHeader, (unsigned int)_countof(lineHeader));

		if (res == EOF)
		{
			fclose(file);
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			XMFLOAT3 vert;
			fscanf_s(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
			temp_verts.push_back(vert);
		} 

		else if (strcmp(lineHeader, "vt") == 0)
		{
			XMFLOAT2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = 1.0f - uv.y;
			temp_uvs.push_back(uv);
		}

		else if (strcmp(lineHeader, "vn") == 0)
		{
			XMFLOAT3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0)
		{
			int vInd[3], uvInd[3], nInd[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vInd[0], &uvInd[0], &nInd[0],
				&vInd[1], &uvInd[1], &nInd[1], &vInd[2], &uvInd[2],
				&nInd[2]);

			if (matches != 9)
			{
				printf("Index read failed.\n");
				return false;
			}

			vInds.push_back(vInd[0]);
			vInds.push_back(vInd[1]);
			vInds.push_back(vInd[2]);
			uvInds.push_back(uvInd[0]);
			uvInds.push_back(uvInd[1]);
			uvInds.push_back(uvInd[2]);
			nInds.push_back(nInd[0]);
			nInds.push_back(nInd[1]);
			nInds.push_back(nInd[2]);
		}
	}

	for (unsigned int i = 0; i < vInds.size(); ++i)
	{
		VertexOBJ tempVert;
		unsigned int vInd = vInds[i];
		unsigned int uvInd = uvInds[i];
		unsigned int nInd = nInds[i];

		XMFLOAT3 vert = temp_verts[vInd - 1];
		XMFLOAT2 uv = temp_uvs[uvInd - 1];
		XMFLOAT3 normal = temp_normals[nInd - 1];

		tempVert.pos = vert;
		tempVert.uv = uv;
		tempVert.normals = normal;

		_outVert.push_back(tempVert);
		_outInd.push_back(i);
	}

	return true;
}

