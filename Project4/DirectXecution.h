#pragma once
class DirectXecution
{

private:
	//Generic Variables
	UsefulStuff											utility;
	UINT												cubeInd[36];
	std::vector<VertexOBJ>								objVerts;
	std::vector<unsigned int>							objInds;

	//Matricies
	XMFLOAT4X4											cubeMat;
	XMFLOAT4X4											objMat;

	//Struct defines
	Vertex												platformVerts[6];
	Vertex												cubeVerts[24];
	RectF												cubeRect;
	Send_To_VRAM										vramData;

	//DirectX variables
	Microsoft::WRL::ComPtr<ID3D11Device>				m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_pContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pcubeInputLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pobjInputLayout = nullptr;
	D3D_DRIVER_TYPE										m_DriverType;
	D3D_FEATURE_LEVEL									m_FeatureLevel;
	D3D11_VIEWPORT										m_ViewPort;
	HRESULT												result;

	//DirectX buffers
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pobjVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pobjIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstBuffer = nullptr;

	//DirectX shaders
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pcubeVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pobjVertShader = nullptr;
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
	void DirectXInit(HWND _window);
	void DirectXRun(DirectX::XMFLOAT4X4 &_camera);
	void ResizeUpdate(HWND _window);
	void DX11Setup(HWND _window);
	HRESULT CreateVertexBuffer();
	HRESULT CreateVertexBuffer(std::vector<VertexOBJ> &_vertVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer(std::vector<unsigned int> _indVect, Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer);
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstBuffer();
	HRESULT CreateDepthStencil();
	HRESULT CreateCubeLayout();
	HRESULT CreateOBJLayout();
	void DrawCube();
	void DrawOBJ(Microsoft::WRL::ComPtr<ID3D11Buffer> &_buffer, std::vector<VertexOBJ> _verts);
};

