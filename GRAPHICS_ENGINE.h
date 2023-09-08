#pragma once
#include <d3d11.h>


class GRAPHICS_ENGINE
{
public:
	GRAPHICS_ENGINE();
	//Initialize the GraphicsEngine and DirectX 11 Device
	bool init();
	//Release all the resources loaded
	bool release();
	~GRAPHICS_ENGINE();
public:
	static GRAPHICS_ENGINE* get();

private:

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

};

