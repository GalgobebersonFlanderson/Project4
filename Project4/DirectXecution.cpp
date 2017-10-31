#include "stdafx.h"

DirectXecution::DirectXecution()
{
}


DirectXecution::~DirectXecution()
{
}

void DirectXecution::DirectXInit(HWND _window)
{
	//Model load
	//bool bResult;
	//bResult = utility.LoadOBJFile("BMW850.obj", verts, uvs, normals);

	//Cube setup
	cubeRect.left = -0.5f;
	cubeRect.right = 0.5f;
	cubeRect.top = 0.5f;
	cubeRect.bottom = -0.5f;
	utility.GenerateCubeVertsAndIndices(cubeVerts, 0.5f, cubeRect, cubeInd);

	//Initialize directX11
	DX11Setup(_window);

	//Create texture
	result = CreateDDSTextureFromFile(m_pDevice.Get(), L"bricks.dds", (ID3D11Resource**)m_pBrickTexture.GetAddressOf(), m_pSrv.GetAddressOf());

	//Create stencil
	result = CreateDepthStencil();

	//Create buffers
	result = CreateVertexBuffer();
	result = CreateIndexBuffer();
	//result = CreateVertexBuffer(verts, m_pBmwVertexBuffer);
	result = CreateConstBuffer();

	//Const buffer world and proj matricies setup
	DirectX::XMStoreFloat4x4(&vramData.worldMat, DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&vramData.projMat, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(55.0f), (float)BufferHeight / (float)BufferWidth, 0.1f, 100.0f)));

	//Create shaders
	result = m_pDevice->CreateVertexShader(VertexShader, sizeof(VertexShader), NULL, m_pVertexShader.GetAddressOf());
	result = m_pDevice->CreatePixelShader(PixelShader, sizeof(PixelShader), NULL, m_pPixelShader.GetAddressOf());

	//Setup layout
	D3D11_INPUT_ELEMENT_DESC vertexShaderLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMALS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//Create input layout
	result = m_pDevice->CreateInputLayout(vertexShaderLayout, ARRAYSIZE(vertexShaderLayout), VertexShader, sizeof(VertexShader), m_pInputLayout.GetAddressOf());

	//Create RTV
	result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_pBackBufferTexture.GetAddressOf()));
	CD3D11_RENDER_TARGET_VIEW_DESC RTVDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture.Get(), &RTVDesc, m_pRtv.GetAddressOf());

	//Create viewport
	m_ViewPort.Width = static_cast<float>(BufferWidth);
	m_ViewPort.Height = static_cast<float>(BufferHeight);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
}

void DirectXecution::DirectXRun(DirectX::XMFLOAT4X4 &_camera)
{
	//Setting const buffer view matrix
	DirectX::XMStoreFloat4x4(&vramData.viewMat, DirectX::XMMatrixTranspose(XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&_camera))));

	//Binding depth stencil
	m_pContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);

	//Binding RTV
	m_pContext->OMSetRenderTargets(1, m_pRtv.GetAddressOf(), m_pDepthStencilView.Get());

	//Clearing RTV
	m_pContext->ClearRenderTargetView(m_pRtv.Get(), DirectX::Colors::WhiteSmoke);

	//Clearing stencil
	m_pContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	//Binding viewport
	m_pContext->RSSetViewports(1, &m_ViewPort);

	//Binding buffers
	UINT cubeVertStride = sizeof(Vertex);
	UINT cubeVertOffset = 0;
	UINT cubeIndOffset = 0;
	m_pContext->UpdateSubresource(m_pConstBuffer.Get(), 0, NULL, &vramData, 0, 0);
	m_pContext->IASetVertexBuffers(0, 1, m_pCubeVertexBuffer.GetAddressOf(), &cubeVertStride, &cubeVertOffset);
	m_pContext->IASetIndexBuffer(m_pCubeIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, cubeIndOffset);

	//Binding topology
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Binding input layout
	m_pContext->IASetInputLayout(m_pInputLayout.Get());

	//Binding shaders
	m_pContext->VSSetShader(m_pVertexShader.Get(), 0, 0);
	m_pContext->VSSetConstantBuffers(0, 1, m_pConstBuffer.GetAddressOf());
	m_pContext->PSSetShader(m_pPixelShader.Get(), 0, 0);

	//Binding SRV
	ID3D11ShaderResourceView* texViews[] = { m_pSrv.Get() };
	m_pContext->PSSetShaderResources(0, ARRAYSIZE(texViews), texViews);

	//Draw
	m_pContext->DrawIndexed(ARRAYSIZE(cubeInd), 0, 0);

	//Display stuff on screen
	m_pSwapChain->Present(0, 0);
}

void DirectXecution::ResizeUpdate(HWND _window)
{
	RECT windowRect;
	unsigned int width, height;

	GetClientRect(_window, &windowRect);
	width = windowRect.right - windowRect.left;
	height = windowRect.bottom - windowRect.top;

	m_pRtv.Reset();
	m_pDepthStencil.Reset();
	result = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

	//Create viewport
	m_ViewPort.Width = static_cast<float>(width);
	m_ViewPort.Height = static_cast<float>(height);
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;

	//Depth stencil description
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Resource
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = NULL;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Height = height;
	depthStencilDesc.Width = width;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.MiscFlags = NULL;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	//View
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	//Create RTV
	result = m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(m_pBackBufferTexture.GetAddressOf()));
	CD3D11_RENDER_TARGET_VIEW_DESC RTVDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
	result = m_pDevice->CreateRenderTargetView(m_pBackBufferTexture.Get(), &RTVDesc, m_pRtv.GetAddressOf());

	//Create stencil
	result = m_pDevice->CreateTexture2D(&depthStencilDesc, NULL, m_pDepthStencil.GetAddressOf());
	result = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, m_pDepthStencilState.GetAddressOf());
	result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &depthStencilViewDesc, m_pDepthStencilView.GetAddressOf());

	//Reset camera
	DirectX::XMStoreFloat4x4(&vramData.projMat, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(55.0f), (float)width / (float)height, 0.1f, 100.0f)));
}

//For self-made cube
HRESULT DirectXecution::CreateVertexBuffer()
{
	//Cube vertex buffer description
	D3D11_BUFFER_DESC cubeVertBufferDesc;
	ZeroMemory(&cubeVertBufferDesc, sizeof(cubeVertBufferDesc));
	cubeVertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	cubeVertBufferDesc.ByteWidth = sizeof(Vertex) * 24;
	cubeVertBufferDesc.CPUAccessFlags = NULL;
	cubeVertBufferDesc.MiscFlags = NULL;
	cubeVertBufferDesc.StructureByteStride = sizeof(Vertex);
	cubeVertBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube vertex initial data
	D3D11_SUBRESOURCE_DATA cubeVertInitData;
	ZeroMemory(&cubeVertInitData, sizeof(cubeVertInitData));
	cubeVertInitData.pSysMem = cubeVerts;
	cubeVertInitData.SysMemPitch = NULL;
	cubeVertInitData.SysMemSlicePitch = NULL;

	//Create cube buffer
	result = m_pDevice->CreateBuffer(&cubeVertBufferDesc, &cubeVertInitData, m_pCubeVertexBuffer.GetAddressOf());

	return result;
}

//For OBJ files
HRESULT DirectXecution::CreateVertexBuffer(std::vector<XMFLOAT3> &_vertVect, Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer)
{
	//OBJ vertex buffer description
	D3D11_BUFFER_DESC objVertBufferDesc;
	ZeroMemory(&objVertBufferDesc, sizeof(objVertBufferDesc));
	objVertBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	objVertBufferDesc.ByteWidth = sizeof(_vertVect) * (UINT)_vertVect.size();
	objVertBufferDesc.CPUAccessFlags = NULL;
	objVertBufferDesc.MiscFlags = NULL;
	objVertBufferDesc.StructureByteStride = sizeof(_vertVect);
	objVertBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//OBJ vertex initial data
	D3D11_SUBRESOURCE_DATA objVertInitData;
	ZeroMemory(&objVertInitData, sizeof(objVertInitData));
	objVertInitData.pSysMem = &_vertVect;
	objVertInitData.SysMemPitch = NULL;
	objVertInitData.SysMemSlicePitch = NULL;

	//Create OBJ buffer
	result = m_pDevice->CreateBuffer(&objVertBufferDesc, &objVertInitData, _buffer.GetAddressOf());

	return result;
}

//For self-made cube
HRESULT DirectXecution::CreateIndexBuffer()
{
	//Cube index buffer description
	D3D11_BUFFER_DESC cubeIndBufferDesc;
	ZeroMemory(&cubeIndBufferDesc, sizeof(cubeIndBufferDesc));
	cubeIndBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	cubeIndBufferDesc.ByteWidth = sizeof(int) * 36;
	cubeIndBufferDesc.CPUAccessFlags = NULL;
	cubeIndBufferDesc.MiscFlags = NULL;
	cubeIndBufferDesc.StructureByteStride = sizeof(int);
	cubeIndBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	//Cube index initial data
	D3D11_SUBRESOURCE_DATA cubeIndInitData;
	ZeroMemory(&cubeIndInitData, sizeof(cubeIndInitData));
	cubeIndInitData.pSysMem = cubeInd;
	cubeIndInitData.SysMemPitch = NULL;
	cubeIndInitData.SysMemSlicePitch = NULL;

	result = m_pDevice->CreateBuffer(&cubeIndBufferDesc, &cubeIndInitData, m_pCubeIndexBuffer.GetAddressOf());

	return result;
}

HRESULT DirectXecution::CreateConstBuffer()
{
	//Const buffer description
	D3D11_BUFFER_DESC constBufferDesc;
	ZeroMemory(&constBufferDesc, sizeof(constBufferDesc));
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.ByteWidth = sizeof(Send_To_VRAM);
	constBufferDesc.CPUAccessFlags = NULL;
	constBufferDesc.MiscFlags = NULL;
	constBufferDesc.StructureByteStride = NULL;
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	//Const buffer initial data
	D3D11_SUBRESOURCE_DATA constBufferInitData;
	ZeroMemory(&constBufferInitData, sizeof(constBufferInitData));
	constBufferInitData.pSysMem = &vramData;
	constBufferInitData.SysMemPitch = NULL;
	constBufferInitData.SysMemSlicePitch = NULL;

	result = m_pDevice->CreateBuffer(&constBufferDesc, &constBufferInitData, m_pConstBuffer.GetAddressOf());

	return result;
}

HRESULT DirectXecution::CreateDepthStencil()
{
	//Depth stencil description
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(depthStencilStateDesc));
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//Resource
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = NULL;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Height = BufferHeight;
	depthStencilDesc.Width = BufferWidth;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.MiscFlags = NULL;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

	//State
	depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilStateDesc.StencilEnable = true;
	depthStencilStateDesc.StencilReadMask = 0xFF;
	depthStencilStateDesc.StencilWriteMask = 0xFF;
	depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//View
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = m_pDevice->CreateTexture2D(&depthStencilDesc, NULL, m_pDepthStencil.GetAddressOf());
	if (result != S_OK)
		return result;
	result = m_pDevice->CreateDepthStencilState(&depthStencilStateDesc, m_pDepthStencilState.GetAddressOf());
	if (result != S_OK)
		return result;
	result = m_pDevice->CreateDepthStencilView(m_pDepthStencil.Get(), &depthStencilViewDesc, m_pDepthStencilView.GetAddressOf());

	return result;
}

void DirectXecution::DX11Setup(HWND _window)
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT driverCount = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};
	UINT featureCount = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = BufferWidth;
	swapDesc.BufferDesc.Height = BufferHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Flags = NULL;
	swapDesc.OutputWindow = _window;

	for (unsigned int i = 0; i < driverCount; ++i)
	{
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
			featureLevels, featureCount, D3D11_SDK_VERSION, &swapDesc, m_pSwapChain.GetAddressOf(), m_pDevice.GetAddressOf(),
			&m_FeatureLevel, m_pContext.GetAddressOf());

		if (SUCCEEDED(result))
		{
			m_DriverType = driverTypes[i];
			break;
		}
	}
}
