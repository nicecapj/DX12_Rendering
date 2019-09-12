#pragma once

#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>
#include <stdint.h>
#include <comdef.h>
#include "d3dx12.h"
#include "D3DUtil.h"
#include "GameTimer.h"
#include "FrameResource.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

// Lightweight structure stores parameters to draw a shape.  This will
// vary from app-to-app.
struct RenderItem
{
	RenderItem() = default;

	// World matrix of the shape that describes the object's local space
	// relative to the world space, which defines the position, orientation,
	// and scale of the object in the world.
	XMFLOAT4X4 World = MathHelper::Identity4x4();

	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();

	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
	// Because we have an object cbuffer for each FrameResource, we have to apply the
	// update to each FrameResource.  Thus, when we modify obect data we should set 
	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
	int NumFramesDirty = gNumFrameResources;

	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
	UINT ObjCBIndex = -1;

	Material* Mat = nullptr;
	MeshGeometry* Geo = nullptr;

	// Primitive topology.
	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// DrawIndexedInstanced parameters.
	UINT IndexCount = 0;
	UINT StartIndexLocation = 0;
	int BaseVertexLocation = 0;
};

class D3DApp
{
public:

	D3DApp(const D3DApp& rhs) = delete;
	D3DApp& operator=(const D3DApp& rhs) = delete;
	virtual ~D3DApp();

	static D3DApp& GetInstance();

	virtual bool Initialize(HWND InWindowHandle);
	//virtual void Update(const GameTimer& gt)/* = 0*/; // data update
	virtual void Draw(const GameTimer& gt)/* = 0*/; // command list update
	virtual void OnResize();

protected:

	void FlushCommandQueue();

	virtual void CreateCommandObjects();
	virtual void CreateSwapChain(HWND InWindowHandle);
	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void CreateFrameResources();

	//virtual void OnResize();
	//virtual void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	ID3D12Resource* GetCurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

	int ClientWidth = 800;
	int ClientHeight = 600;

private:

	D3DApp();

private:

	static D3DApp* Instance;

	// COM(Component Object Model)
	// The COM object is like a C++ class.
	// DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���

	// ��� ������ : C++�� C++�νḸ ����� �� �ְ� ��
	// ���� ȣȯ�� : ���ο� �����Ͽ� ����� �� �ְ� ��

	// �����ڸ�, Com �������̽��� �ϳ��� Ŭ���� ������Ʈ�� �����ϰ� ����ϸ� �ȴٴ� �ǹ�

	// ComPtr is like a smart pointer.
	ComPtr<ID3D12Device> D3D12Device; // Render�� ���� ����� ��� �ִ� �������̽�
	
	// DirectX Graphics Infrastructure : ���� �׷��� API
	ComPtr<IDXGIFactory4> DxgiFactory; // Swap chain �������̽� ����, ���÷��� �����(= �׷���ī��) ����
	ComPtr<IDXGISwapChain> SwapChain; // ȭ���� ǥ���ϴ� ����/�ĸ� ���۸� ��ȯ���ִ� �������̽�(���� ���۸�)

	// Views
	// Resource(=�ؽ�ó)���� ���� ������ ���������ο� �ѱ�°� �ƴ϶�,
	// Descriptor�� Resource���� �����Ͽ� ������ ���������ο� �ѱ��.
	// ��, Descriptor�� Resource�� GPU ���̸� �̾��ִ� ������ �ڷᱸ���̴�.
	// (Descriptor�� Resource���� �ּҸ� ��� �ְ�, GPU�� �̸� �����Ͽ� ������)
	// �̷��� GPU�� ���������� �����ϴ� ������
	// 1. Resource�� ���� �������� ���� �� �ֱ� �����̴�.
	// 2. Resource�� �� ��ü�� � ����� �ϴ��� �� �� ���� �����̴�.
	// ��, Descriptor�� Resource�� ��� � ����� �ϴ����� ���� ������ ��� ������
	// �������� ��� ������ ��� �κп����� ����� �� �ִ�.
	// �������ڸ�, Descriptor�� Resource�� �ּ�, Resource�� ���, ���ó�� ���� ������ ��� �ִ� �ڷᱸ���̴�.
	// Descriptor Heap : Descriptor �迭
	// �ϳ��� Resource�� RtvHeap���� �� �� �ְ�, DsvHeap���� �� �� �ִ�.
	ComPtr<ID3D12DescriptorHeap> RtvHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap> DsvHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap> SrvHeap = nullptr;

	UINT RtvDescriptorSize = 0;			// Render target view
	UINT DsvDescriptorSize = 0;			// Depth stencil view
	UINT CbvSrvUavDescriptorSize = 0;	// Constant buffer, Shader resource, Unordered access view

	bool IsMsaa4xState = false;		// 4X MSAA enabled
	UINT Msaa4xQuality = 0;			// quality level of 4X MSAA

	ComPtr<ID3D12Fence> Fence;
	UINT64 CurrentFenceCount = 0;

	// The interaction between CPU and GPU
	// CPU���� ������ �ִ� ��ɵ�(Command list)�� GPU�� ��� ��⿭(Command queue)�� �ѱ��.
	ComPtr<ID3D12CommandQueue> CommandQueue; // GPU �׸��� ��� ��⿭
	ComPtr<ID3D12GraphicsCommandList> CommandList; // CPU �׸��� ��ɵ�
	ComPtr<ID3D12CommandAllocator> CommandListAllocator; // Command list�� �޸𸮸� �Ҵ��ϴ� �Ҵ���

	D3D12_VIEWPORT ScreenViewport;
	D3D12_RECT ScissorRect;

	ComPtr<ID3D12PipelineState> OpaquePipelineStateObject = nullptr;

	// Buffers
	static const int SwapChainBufferCount = 2;
	ComPtr<ID3D12Resource> SwapChainBuffer[SwapChainBufferCount];
	int CurBackBufferIndex = 0;

	ComPtr<ID3D12Resource> DepthStencilBuffer;
	DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	// root
	ComPtr<ID3D12RootSignature> RootSignature = nullptr;

	// frame resources
	std::unique_ptr<FrameResource> CurFrameResource;

	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	// Render items divided by PSO.
	std::vector<RenderItem*> OpaqueRitems;
	 
	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> AllRitems;
};