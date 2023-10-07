#pragma once
#include <d3d11.h>

class DEVICECONTEXT;

class INDEXBUFFER
{
public:
	INDEXBUFFER();
	bool load(void* list_indices, UINT size_list);
	UINT getSizeIndexList();
	bool release();
	~INDEXBUFFER();

private:
	UINT m_size_list;
	ID3D11Buffer* m_buffer;

	friend class DEVICECONTEXT;
};
