#pragma once
#include <d3d11.h>

class DEVICECONTEXT;

class CONSTANTBUFFER
{
public:
	CONSTANTBUFFER();
	bool load(void* buffer, UINT size_buffer);
	void update(DEVICECONTEXT* context, void* buffer);
	bool release();
	~CONSTANTBUFFER();
private:
	ID3D11Buffer* m_buffer;

	friend class DEVICECONTEXT;
};

