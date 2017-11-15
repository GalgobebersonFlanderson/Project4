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
#include "SkyboxPixelShader.csh"
#include "VertexShader.csh"
#include "objVertexShader.csh"
#include "SkyboxVertexShader.csh"
#include "InstancedVertexShader.csh"
#include <DirectXColors.h>
#include "Defines.h"

//Enums
enum LightType { DirectionalLight, PointLight, SpotLight };
enum ConstBufferStruct { MatrixBuffer, MaterialBuffer, LightBuffer, InstancedMatrixBuffer };

// Structures
struct Vertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
	DirectX::XMFLOAT3 normals;
	DirectX::XMFLOAT2 uv;
};

struct VertexOBJ
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normals;
	DirectX::XMFLOAT2 uv;
};

struct Send_To_VRAM
{
	DirectX::XMFLOAT4X4 worldMat;
	DirectX::XMFLOAT4X4 viewMat;
	DirectX::XMFLOAT4X4 projMat;
};

struct Send_To_VRAM_Instanced
{
	DirectX::XMFLOAT4X4 worldMat[4];
	DirectX::XMFLOAT4X4 viewMat;
	DirectX::XMFLOAT4X4 projMat;
};

struct RectF
{
	float top, left, bottom, right;
};

struct _Material
{
	_Material()
		: emissive(0.0f, 0.0f, 0.0f, 1.0f)
		, ambient(0.1f, 0.1f, 0.1f, 1.0f)
		, diffuse(1.0f, 1.0f, 1.0f, 1.0f)
		, specular(1.0f, 1.0f, 1.0f, 1.0f)
		, specularPower(125.0f)
		, useTexture(false)
	{}

	DirectX::XMFLOAT4 emissive;
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;
	float specularPower;
	bool useTexture;
	DirectX::XMFLOAT2 padding;
};

struct MaterialProperties
{
	_Material material;
};

struct Light
{
	Light()
		: pos(0.0f, 0.0f, 0.0f, 1.0f)
		, dir(0.0f, 0.0f, 1.0f, 0.0f)
		, color(1.0f, 1.0f, 1.0f, 1.0f)
		, spotAngle(45.0f)
		, attenuation(1.0f, 0.0f, 0.0f)
		, lightType(DirectionalLight)
		, enabled(0)
	{}

	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 dir;
	DirectX::XMFLOAT4 color;
	float spotAngle;
	DirectX::XMFLOAT3 attenuation; //x = constAtt, y = linAtt, z = quadAtt
	int lightType;
	bool enabled;
	int padding[2];
};

struct LightProperties
{
	LightProperties()
		: eyePos(0.0f, 0.0f, 0.0f, 1.0f)
		, globalAmbient(0.5f, 0.5f, 0.5f, 1.0f)
	{}

	DirectX::XMFLOAT4 eyePos;
	DirectX::XMFLOAT4 globalAmbient;
	Light lights[3];
};

#include <vector>
#include <DirectXMath.h>
#include <dxgiformat.h>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <wrl/client.h>
#include "UsefulStuff.h"
#include "XTime.h"
#include "DirectXecution.h"
#include "DDSTextureLoader.h"
#include "Project4.h"