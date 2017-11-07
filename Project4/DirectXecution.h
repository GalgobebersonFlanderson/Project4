#pragma once
class DirectXecution
{

private:
	//Generic Variables
	UsefulStuff											utility;
	UINT												cubeInd[36];
	std::vector<VertexOBJ>								pattyVerts;
	std::vector<unsigned int>							pattyInds;
	std::vector<VertexOBJ>								floorVerts;
	std::vector<unsigned int>							floorInds;
	float												angleY, nearP, farP, width, height;

	//Matricies
	XMMATRIX											cubeMat = XMMatrixIdentity();
	XMMATRIX											pattyMat = XMMatrixIdentity();
	XMMATRIX											floorMat = XMMatrixIdentity();

	//Struct defines
	Vertex												platformVerts[6];
	Vertex												cubeVerts[24];
	RectF												cubeRect;
	Send_To_VRAM										vramData;

	//DirectX variables
	Microsoft::WRL::ComPtr<ID3D11Device>				m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			m_pContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain>				m_pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pCubeInputLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			m_pObjInputLayout = nullptr;
	D3D_DRIVER_TYPE										m_DriverType;
	D3D_FEATURE_LEVEL									m_FeatureLevel;
	D3D11_VIEWPORT										m_ViewPort;
	HRESULT												result;

	//DirectX buffers
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pPattyVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pCubeIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pPattyIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pFloorIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pConstBuffer = nullptr;

	//DirectX shaders
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pCubeVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			m_pObjVertShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			m_pPixelShader = nullptr;

	//Views
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		m_pRtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pCubeSrv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pPattySrv = nullptr;

	//Resources
	Microsoft::WRL::ComPtr<ID3D11Resource>				m_pResource = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pBrickTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				m_pPattyTexture = nullptr;

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
	void DrawOBJ(Microsoft::WRL::ComPtr<ID3D11Buffer> &_vBuffer, Microsoft::WRL::ComPtr<ID3D11Buffer> &_iBuffer, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> &_srv, XMMATRIX &_mat, std::vector<VertexOBJ> _verts, std::vector<unsigned int> _inds);
	void AdjZoomAndNearFarCheck(float _angleVal, float _nearFarVal);
};

