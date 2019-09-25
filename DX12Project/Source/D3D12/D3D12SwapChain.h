#pragma once
#include <dxgi.h>
#include <d3d12.h>

using namespace Microsoft::WRL;

class D3D12SwapChain
{
public:
	D3D12SwapChain() = delete;
	D3D12SwapChain(class D3D12Device* InDevice);
	virtual ~D3D12SwapChain() {}

	void OnResize(class D3D12Device* InDevice);
	ID3D12Resource* GetCurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
	unsigned int GetSwapChainBufferCount() { return SwapChainBufferCount; }

	void Create(class D3D12Device* InDevice, class D3D12CommandListExecutor* InExecutor);
	void SwapChainToFrontBuffer();

private:
	// ȭ���� ǥ���ϴ� ����/�ĸ� ���۸� ��ȯ���ִ� �������̽�(���� ���۸�)
	ComPtr<IDXGISwapChain> SwapChain = nullptr;

	int ClientWidth = 800;
	int ClientHeight = 600;
	bool IsMsaa4xState = false;		// 4X MSAA enabled
	UINT Msaa4xQuality = 0;			// quality level of 4X MSAA

	// Buffers
	static const unsigned int SwapChainBufferCount = 2;
	class D3D12Resource* SwapChainBuffer[SwapChainBufferCount];

	int CurBackBufferIndex = 0;

	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// descriptor
	class D3D12Descriptor* RenderTargetViewDesc = nullptr;
};