#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include "MathHelper.h"

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

	ComPtr<ID3D12Device> GetDevice() { return Device; }
	ComPtr<IDXGIFactory4> GetDxgi() { return DxgiFactory; }

	HWND GetWindowHandle() { return MainWindowHandle; }

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