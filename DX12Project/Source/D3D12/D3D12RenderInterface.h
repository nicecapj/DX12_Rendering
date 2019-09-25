#pragma once

#include "MathHelper.h"
#include "FrameResource.h"

using namespace DirectX;

// �̰� �������� ��������
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

class D3D12RenderInterface
{
public:
	D3D12RenderInterface();
	~D3D12RenderInterface();

	// test -> virtual
	void CreateRenderTarget();
	void CreateDepthStencil();
	void CreateShaderBuffer();

	void CreateFrameResources();
	void DrawRenderItems(class D3D12CommandList* cmdList);

	// �ʼ�
	void Update();

private:
	// frame resources
	std::unique_ptr<FrameResource> CurFrameResource;

	// Render items divided by PSO.
	std::vector<RenderItem*> OpaqueRitems;

// 	// List of all the render items.
// 	std::vector<std::unique_ptr<RenderItem>> AllRitems;

	class D3D12Device* Device = nullptr;
	class D3D12SwapChain* SwapChain = nullptr;
	class D3D12CommandListExecutor* CmdListExecutor = nullptr;
};

