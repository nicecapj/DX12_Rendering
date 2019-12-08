#pragma once

#include <d3d12.h>
#include "MathHelper.h"
#include "D3D12Device.h"

class D3D12Descriptor
{
public:
	D3D12Descriptor() = delete;
	D3D12Descriptor(class D3D12Device* InDevice, D3D12_DESCRIPTOR_HEAP_DESC& InHeapDesc, D3D12_DESCRIPTOR_HEAP_TYPE InDescriptorType)
	{
		if (InDevice)
		{
			ComPtr<ID3D12Device> pD3D12Device = InDevice->GetDevice();
			if (pD3D12Device)
			{
				Size = pD3D12Device->GetDescriptorHandleIncrementSize(InDescriptorType);

				ThrowIfFailed(pD3D12Device->CreateDescriptorHeap(&InHeapDesc, IID_PPV_ARGS(DescriptorHeap.GetAddressOf())));
			}
		}
	}
	virtual ~D3D12Descriptor() {}

	UINT GetSize() { return Size; }
	void SetSize(UINT InSize) { Size = InSize; }
	ComPtr<ID3D12DescriptorHeap> GetDescriptor() { return DescriptorHeap; }

private:
	ComPtr<ID3D12DescriptorHeap> DescriptorHeap = nullptr;
	UINT Size = 0;
};
