#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include "d3dx12.h"
#include "MathHelper.h"
#include "D3DUtil.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class D3DDeviceBase
{
public:
	D3DDeviceBase() {}
	virtual ~D3DDeviceBase() {}
};

class D3D12Device : public D3DDeviceBase
{
public:
	D3D12Device(HWND InWindowHandle);
	virtual ~D3D12Device();

	ComPtr<ID3D12Device> Get() { ReturnCheckAssert(Device); }
	ID3D12Device* GetInterface() { assert(Device); ReturnCheckAssert(Device.Get()); }
	ComPtr<IDXGIFactory4> GetDxgi() { ReturnCheckAssert(DxgiFactory); }
	HWND GetWindowHandle() { ReturnCheckAssert(MainWindowHandle); }

	// Command interfaces
	void CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE InCommandListType, ComPtr<ID3D12CommandAllocator>& InCommandAllocator);
	void CreateCommandList(D3D12_COMMAND_LIST_TYPE InCommandListType, ComPtr<ID3D12CommandAllocator>& InCommandAllocator, ComPtr<ID3D12GraphicsCommandList>& InCommandList);
	void CreateCommandQueue(D3D12_COMMAND_QUEUE_DESC& InQueueDesc, ComPtr<ID3D12CommandQueue>& InCommandQueue);

	// Swap chain interfaces
	void CreateSwapChain(class D3D12CommandListExecutor* InExecutor, class D3D12SwapChain* InSwapChain, DXGI_SWAP_CHAIN_DESC& InSwapChainDesc);
	void CheckFeatureSupport(D3D12_FEATURE InFeature, D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS& InMultisampleQualityLevels);

	// Resource interfaces
	void CreateCommittedResource(ComPtr<ID3D12Resource>& InResource, D3D12_HEAP_TYPE InHeapType, D3D12_HEAP_FLAGS InHeapFlags, D3D12_RESOURCE_DESC& InDesc, D3D12_RESOURCE_STATES InResourceStates, D3D12_CLEAR_VALUE InValue);
	void CreateRenderTargetView(ComPtr<ID3D12Resource>& InResource, const D3D12_RENDER_TARGET_VIEW_DESC* InDesc, CD3DX12_CPU_DESCRIPTOR_HANDLE& InDescriptorHandle);
	void CreateDepthStencilView(ComPtr<ID3D12Resource>& InResource, class D3D12Descriptor* InDescriptor, D3D12_DEPTH_STENCIL_VIEW_DESC& InDepthStencilDesc);
	void CreateShaderView(ComPtr<ID3D12Resource>& InResource, class D3D12Descriptor* InDescriptor, D3D12_SHADER_RESOURCE_VIEW_DESC& InShaderDesc);

	// Descriptor interfaces
	UINT GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE InDescriptorHeapType);

	// Pipeline state interfaces
	void CreateGraphicsPipelineState(ComPtr<ID3D12PipelineState> InPipelineState, D3D12_GRAPHICS_PIPELINE_STATE_DESC& InPipelineStateDesc);

private:
	void CreateDevice();

private:
	// COM(Component Object Model)
	// The COM object is like a C++ class.
	// DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���

	// ��� ������ : C++�� C++�νḸ ����� �� �ְ� ��
	// ���� ȣȯ�� : ���ο� �����Ͽ� ����� �� �ְ� ��

	// �����ڸ�, Com �������̽��� �ϳ��� Ŭ���� ������Ʈ�� �����ϰ� ����ϸ� �ȴٴ� �ǹ�

	// ComPtr is like a smart pointer.
	ComPtr<ID3D12Device> Device; // Render�� ���� ����� ��� �ִ� �������̽�

	// DirectX Graphics Infrastructure : ���� �׷��� API
	ComPtr<IDXGIFactory4> DxgiFactory; // Swap chain �������̽� ����, ���÷��� �����(= �׷���ī��) ����

	HWND MainWindowHandle = nullptr;
};