#include "D3DXRenderEngine.h"
#include "GBAssert.h"
#include "Win32Utils.h"
#include "MacroHeader.h"
#include "D3DXVertex.h"
#include "D3DXGlobalFunction.h"

extern void GameDraw(IDirect3DDevice9* device, ID3DXSprite* sprite);

D3DXRenderEngine::D3DXRenderEngine()
	:RenderEngine((void**)(&m_device)), 
	m_d3pp(nullptr), m_device(nullptr), m_sprite(nullptr), m_font(nullptr),
	m_curProgram(&m_defProgram)
{
	D3DXMatrixIdentity(&m_vMatrix);
	D3DXMatrixIdentity(&m_pMatrix);
	D3DXMatrixIdentity(&Identify_Matrix);
}

void D3DXRenderEngine::setOrthoMatrix(float _width, float _height, float _near, float _far)
{
	D3DXMatrixOrthoRH(&m_vMatrix, _width, _height, _near, _far);
}

void D3DXRenderEngine::setLookAtMatrix(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z)
{
	D3DXMatrixLookAtRH(
		&m_pMatrix,
		&D3DXVECTOR3(pos_x, pos_y, pos_z),
		&D3DXVECTOR3(target_x, target_y, target_z),
		&D3DXVECTOR3(up_x, up_y, up_z)
		);
}

void D3DXRenderEngine::init()
{
	HRESULT result = D3D_OK;
	m_d3pp = Direct3DCreate9(D3D_SDK_VERSION);
	GBASSERT(m_d3pp != nullptr);

	D3DPRESENT_PARAMETERS parameters = { 0 };
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	parameters.Windowed = TRUE;

	result = m_d3pp->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Win32Utils::getInstance()->getWin32Window(),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&parameters,
		&m_device
		);
	GBASSERT(result == D3D_OK);

	result = D3DXCreateSprite(m_device, &m_sprite);
	GBASSERT(result == D3D_OK);

	Vertex::init(m_device);

	auto win32_utils = Win32Utils::getInstance();

	D3DXMatrixTranslation(&m_tMatrix, 
		-(win32_utils->getWidth() >> 1), 
		-(win32_utils->getHeight() >> 1),
		0
		);
	setOrthoMatrix(win32_utils->getWidth(), win32_utils->getHeight(), 0, 1);
	setLookAtMatrix(
		0.0f, 0.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
		);

	dxCompileShader(DEFAULT_VSHADER, VS_2_0, &m_defProgram);
	dxCompileShader(DEFAULT_FSHADER, PS_2_0, &m_defProgram);

	m_defProgram.initVTable("v_tMatrix", "tMatrix");
	m_defProgram.initVTable("v_mMatrix", "mMatrix");
	m_defProgram.initVTable("v_vMatrix", "vMatrix");
	m_defProgram.initVTable("v_pMatrix", "pMatrix");
}

void D3DXRenderEngine::render()
{
	m_device->Clear(0, nullptr, D3DCLEAR_TARGET, 0xff000000, 1.0f, 0);
	m_device->BeginScene();
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	inputMatrix();
	GameDraw(m_device, m_sprite);

	m_sprite->End();
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);
}

void D3DXRenderEngine::destroy()
{
	Vertex::destroy();
	SAFE_RELEASE_COM(m_font);
	SAFE_RELEASE_COM(m_sprite);
	SAFE_RELEASE_COM(m_device);
	SAFE_RELEASE_COM(m_d3pp);
}


void D3DXRenderEngine::LinkProgram()
{
	IDirect3DVertexShader9* vShader = m_curProgram->getVShader();
	IDirect3DPixelShader9* fShader = m_curProgram->getFShader();

	if(vShader)
		m_device->SetVertexShader(vShader);
	else
		m_device->SetVertexShader(m_defProgram.getVShader());
	if(fShader)
		m_device->SetPixelShader(fShader);
	else
		m_device->SetPixelShader(m_defProgram.getFShader());
}

void D3DXRenderEngine::setTransformMatrix(const D3DXMATRIX* matrix)
{
	auto vTable = m_defProgram.getVTable();
	if(matrix != nullptr)
		vTable->SetMatrix(m_device, m_defProgram.getHandle("v_mMatrix"), matrix);
	else
		vTable->SetMatrix(m_device, m_defProgram.getHandle("v_mMatrix"), &Identify_Matrix);
}

void D3DXRenderEngine::setProgram(D3DXProgram* program)
{
	if(program != nullptr)
		m_curProgram = program;
	else
		m_curProgram = &m_defProgram;
}

void D3DXRenderEngine::setRenderState(D3DRENDERSTATETYPE State, DWORD val)
{
	HRESULT result = m_device->SetRenderState(State, val);
	GBASSERT(result == D3D_OK);
}

void D3DXRenderEngine::inputMatrix()
{
	auto vTable = m_curProgram->getVTable();
	vTable->SetMatrix(m_device, m_curProgram->getHandle("v_mMatrix"), &Identify_Matrix);
	vTable->SetMatrix(m_device, m_curProgram->getHandle("v_tMatrix"), &m_tMatrix);
	vTable->SetMatrixTranspose(m_device, m_curProgram->getHandle("v_vMatrix"), &m_vMatrix);
	vTable->SetMatrixTranspose(m_device, m_curProgram->getHandle("v_pMatrix"), &m_pMatrix);
}

