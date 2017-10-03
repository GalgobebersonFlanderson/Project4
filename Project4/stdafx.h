// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include "Project4.h"
#include "d3d11.h"
#include "PixelShader.csh"
#include "VertexShader.csh"
#include <DirectXColors.h>

// Structures
struct Vertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normals;
	DirectX::XMFLOAT2 uv;
};

struct RectF
{
	float top, left, bottom, right;
};

#include <DirectXMath.h>
#include "UsefulStuff.h"
#include <wrl/client.h>