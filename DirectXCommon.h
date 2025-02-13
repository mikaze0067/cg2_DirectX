#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "Logger.h"
#include "StringUtility.h"
#include "WinApp.h"
#include <array>

#include <cassert>
#include <dxcapi.h>

#include "externals/imgui/imgui_impl_win32.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include <format>
#include "externals/DirectXTex/DirectXTex.h"
#include <chrono>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

class DirectXCommon {

	/*IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);*/



public: //メンバ変数

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible)
	{
		Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> descriptorHeap = nullptr;
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
		descriptorHeapDesc.Type = heapType;
		descriptorHeapDesc.NumDescriptors = numDescriptors;
		descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
		assert(SUCCEEDED(hr));
		return descriptorHeap;
	}

	Microsoft::WRL::ComPtr <ID3D12Resource>
		CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

	Microsoft::WRL::ComPtr <IDxcBlob>CompileShader(const std::wstring& filePath, const wchar_t* profile);

	Microsoft::WRL::ComPtr <ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	[[nodiscard]]
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	static DirectX::ScratchImage LoadTexture(const std::string& filePath);


	//初期化
	void Initialize(WinApp* winApp);

	void Device();

	void Command();

	void SwapChain();

	void DepthBuffer();

	void DescriptorHeap();

	void RenderTarget();

	void DepthStencilView();

	void Fence();

	void ViewPort();

	void ScissorRect();

	void DXCCompiler();

	void ImGui();

	//描画前処理
	void PreDraw();
	//描画後処理
	void PostDraw();

	void Finalize();


	//SRVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);
	//SRVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	//RTVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUDescriptorHandle(uint32_t index);
	//RTVの指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetRTVGPUDescriptorHandle(uint32_t index);

	//DSVの指定番号のCPUデスクリプタハンドルを取得する
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUDescriptorHandle(uint32_t index);
	//DSVの指定番号のGPUデスクリプタハンドルを取得する
	D3D12_GPU_DESCRIPTOR_HANDLE GetDSVGPUDescriptorHandle(uint32_t index);

	//getter
	ID3D12Device* GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

	//ID3D12Resource* GetTexture() { return texture.Get(); }

	//ID3D12Resource* GetTextureResource() const { return textureResources.Get(); }

	//ID3D12Resource* GetTextureResource2() const { return textureResources2.Get(); }

	//ID3D12Resource* GetTextureResource3() const { return textureResources3.Get(); }


	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index){
		D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
		handleCPU.ptr += (descriptorSize * index);
		return handleCPU;
	}

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index){
		D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
		handleGPU.ptr += (descriptorSize * index);
		return handleGPU;
	}

	const D3D12_DEPTH_STENCIL_DESC& GetDepthStencilDesc() const {
		return depthStencilDesc;
	}



private:
	//FPS固定初期化
	void InitializeFixFPS();
	//FPS固定更新
	void UpdateFixFPS();
	//記録時間（FPS固定用）
	std::chrono::steady_clock::time_point reference_;

#pragma region Device

	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	//DXGIファクトリーの生成
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr < ID3D12Device> device;

	Microsoft::WRL::ComPtr <ID3D12Debug1> debugController;

	//使用するアダプタ用の変数。
	Microsoft::WRL::ComPtr <IDXGIAdapter4> useAdapter;

	Microsoft::WRL::ComPtr <ID3D12InfoQueue> infoQueue;

	D3D12_INFO_QUEUE_FILTER filter{};
#pragma endregion

#pragma region Command

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//コマンドキューを生成する
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> commandQueue;

	//コマンドアロケーターを生成する
	Microsoft::WRL::ComPtr <ID3D12CommandAllocator> commandAllocator;

	//コマンドリストを生成する
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> commandList;
#pragma endregion

#pragma region SwapChain

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
#pragma endregion

	Microsoft::WRL::ComPtr <ID3D12Resource> intermediateResource;

#pragma region DepthBuffer

	//DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};

	D3D12_RESOURCE_DESC resourceDesc{};

	D3D12_HEAP_PROPERTIES heapProperties{};

	D3D12_CLEAR_VALUE depthClerValue{};

	Microsoft::WRL::ComPtr<ID3D12Resource> resource;

#pragma endregion

#pragma region DescriptorHeap

	uint32_t descriptorSizeSRV = 0;
	uint32_t descriptorSizeRTV = 0;
	uint32_t descriptorSizeDSV = 0;

	//ディスクリプターヒープの生成
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> rtvDescriptorHeap;

	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;

	//DSV用のヒープでディスクリプタの数は１
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> dsvDescriptorHeap;
#pragma endregion

#pragma region RenderTarget

	//スワップチェーンを生成する
	Microsoft::WRL::ComPtr <IDXGISwapChain4> swapChain;
	//SwapChainからResourceを引っ張ってくる
	//Microsoft::WRL::ComPtr <ID3D12Resource> swapChainResources[2] = { nullptr };
	//スワップチェーン
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;

	//RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE	rtvHandles[2];
#pragma endregion



#pragma region DepthStencilView

	//DSVの設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};

	Microsoft::WRL::ComPtr <ID3D12Resource> depthStencilResource;
#pragma endregion

#pragma region Fence

	//初期値0でFenceを作る
	Microsoft::WRL::ComPtr <ID3D12Fence> fence;

	uint64_t fenceValue = 0;

	HANDLE fenceEvent;
#pragma endregion

#pragma region Viewport

	D3D12_VIEWPORT viewport{};
#pragma endregion

#pragma region ScissorRect

	D3D12_RECT scissorRect{};
#pragma endregion

#pragma region DXCCompiler

	//dxcCompilerを初期化
	Microsoft::WRL::ComPtr <IDxcUtils> dxcUtils;
	Microsoft::WRL::ComPtr <IDxcCompiler3> dxcCompiler;
	Microsoft::WRL::ComPtr <IDxcIncludeHandler> includeHandler;
#pragma endregion

#pragma region PreDraw

	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};

#pragma endregion

	//WindowsAPI
	WinApp* winApp = nullptr;


};