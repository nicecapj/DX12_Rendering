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
// 
// // Lightweight structure stores parameters to draw a shape.  This will
// // vary from app-to-app.
// struct RenderItem
// {
// 	RenderItem() = default;
// 
// 	// World matrix of the shape that describes the object's local space
// 	// relative to the world space, which defines the position, orientation,
// 	// and scale of the object in the world.
// 	XMFLOAT4X4 World = MathHelper::Identity4x4();
// 
// 	XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();
// 
// 	// Dirty flag indicating the object data has changed and we need to update the constant buffer.
// 	// Because we have an object cbuffer for each FrameResource, we have to apply the
// 	// update to each FrameResource.  Thus, when we modify obect data we should set 
// 	// NumFramesDirty = gNumFrameResources so that each frame resource gets the update.
// 	int NumFramesDirty = gNumFrameResources;
// 
// 	// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
// 	UINT ObjCBIndex = -1;
// 
// 	Material* Mat = nullptr;
// 	MeshGeometry* Geo = nullptr;
// 
// 	// Primitive topology.
// 	D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
// 
// 	// DrawIndexedInstanced parameters.
// 	UINT IndexCount = 0;
// 	UINT StartIndexLocation = 0;
// 	int BaseVertexLocation = 0;
// };

class D3DApp
{
public:

	D3DApp(const D3DApp& rhs) = delete;
	D3DApp& operator=(const D3DApp& rhs) = delete;
	virtual ~D3DApp();

	static D3DApp& GetInstance();

	virtual bool Initialize(HWND InWindowHandle);
	virtual void Update(const GameTimer& gt)/* = 0*/; // data update
	virtual void Draw(const GameTimer& gt)/* = 0*/; // command list update

protected:


private:

	D3DApp();

private:

	static D3DApp* Instance;

	class D3D12RenderInterface* RenderInterface = nullptr;

	ComPtr<ID3D12Fence> Fence;
	UINT64 CurrentFenceCount = 0;

	class D3D12CommandList* CommandList; // �ӽ�

// 	ComPtr<ID3D12PipelineState> OpaquePipelineStateObject = nullptr;
// 
// 	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
// 	XMFLOAT4X4 mView = MathHelper::Identity4x4();
// 	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
// 
// 	float mTheta = 1.3f*XM_PI;
// 	float mPhi = 0.4f*XM_PI;
// 	float mRadius = 2.5f;
// 
// 	POINT mLastMousePos;

// 	// Render items divided by PSO.
// 	std::vector<RenderItem*> OpaqueRitems;
// 
// 	// List of all the render items.
// 	std::vector<std::unique_ptr<RenderItem>> AllRitems;
// 	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
// 	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
// 	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
// 	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
// 
// 	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
};