#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>

IndexBuffer::IndexBuffer() : m_buffer(0)
{
}

void IndexBuffer::load(void* list_indices, UINT size_list)
{
	if (this->m_buffer) this->m_buffer->Release();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * m_size_list;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = list_indices;
	this->m_size_list = m_size_list;

	ID3D11Device* directXDevice = GraphicsEngine::get()->getDirect3DDevice();
	HRESULT bufferResult = directXDevice->CreateBuffer(&bufferDesc, &initData, &this->m_buffer);

	if (SUCCEEDED(bufferResult)) {
		std::cout << "Creation of index buffer succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating a index buffer. \n";
	}


}

UINT IndexBuffer::getIndexListSize()
{
	return this->m_size_list;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}


IndexBuffer::~IndexBuffer()
{
}
