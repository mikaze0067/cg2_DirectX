#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>
#include "WinApp.h"


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;


//DirectX基盤
class DirectXbasis {
public: //メンバ変数

	//初期化
	void Initialize(WinApp* winApp);

	void Device();

	void Command();

	void SwapChain();

	void Depth();

	void DescriptorHeap();

private:
	Microsoft::WRL::ComPtr < ID3D12Device> device;

	//DXGIファクトリーの生成
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	//WindowsAPI
	WinApp* winApp = nullptr;

};