#pragma once
#include <d3d11.h>
#include "DeviceContext.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool load(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	bool release();
	~ConstantBuffer();
private:
	ID3D11Buffer* m_buffer;

	friend class DeviceContext;
};

