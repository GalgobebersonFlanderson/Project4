#pragma once
class DirectXecution
{

private:
	//Generic Variables
	UsefulStuff											utility;
	UINT												cubeInd[36];

	//Struct defines
	Vertex												platformVerts[6];
	Vertex												cubeVerts[24];
	RectF												cubeRect;
	Send_To_VRAM										vramData;

	//DirectX variables
	Microsoft::WRL::ComPtr<ID3D11Device>				m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_pContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pInputLayout = nullptr;
	D3D_DRIVER_TYPE										m_DriverType;
	D3D_FEATURE_LEVEL									m_FeatureLevel;
	D3D11_VIEWPORT										m_ViewPort;

	//DirectX buffers
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstBuffer = nullptr;

	//DirectX shaders
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pVertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pPixelShader = nullptr;

	//Views
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_pRtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pSrv = nullptr;

	//Resources
	Microsoft::WRL::ComPtr<ID3D11Resource>				m_pResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBrickTexture = nullptr;

	//Depth stencil
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		m_pDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		m_pDepthStencilView = nullptr;

public:
	DirectXecution();
	~DirectXecution();
	void DirectXInit(HWND _window, DirectX::XMFLOAT4X4 &_camera);
	void DirectXRun(DirectX::XMFLOAT4X4 &_camera);
};

