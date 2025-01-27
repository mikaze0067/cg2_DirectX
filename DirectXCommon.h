#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp.h"
#include <array>
#include <dxcapi.h>
#include "Logger.h"
#include "StringUtility.h"


class DirectXCommon {

	IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	Microsoft::WRL::ComPtr <ID3D12Resource>
		CreateDepthStencilTextureResource(Microsoft::WRL::ComPtr <ID3D12Device> device, int32_t width, int32_t height);


public: //メンバ変数

	

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

private:

	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	//DXGIファクトリーの生成
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;

	Microsoft::WRL::ComPtr < ID3D12Device> device = nullptr;

	//コマンドキューを生成する
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> commandQueue = nullptr;

	//コマンドアロケーターを生成する
	Microsoft::WRL::ComPtr <ID3D12CommandAllocator> commandAllocator = nullptr;

	//コマンドリストを生成する
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> commandList = nullptr;

	//WindowsAPI
	WinApp* winApp = nullptr;

	//スワップチェーンを生成する
	Microsoft::WRL::ComPtr <IDXGISwapChain4> swapChain = nullptr;
	//SwapChainからResourceを引っ張ってくる
	//Microsoft::WRL::ComPtr <ID3D12Resource> swapChainResources[2] = { nullptr };
	//スワップチェーン
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources;

	uint32_t descriptorSizeSRV = 0;
	uint32_t descriptorSizeRTV = 0;
	uint32_t descriptorSizeDSV = 0;

	//ディスクリプターヒープの生成
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> rtvDescriptorHeap;

	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;

	//DSV用のヒープでディスクリプタの数は１
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> dsvDescriptorHeap;

	

	Microsoft::WRL::ComPtr <ID3D12Resource> depthStencilResource;
	//RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE	rtvHandles[2];

	//初期値0でFenceを作る
	Microsoft::WRL::ComPtr <ID3D12Fence> fence = nullptr;

	uint64_t fenceValue = 0;

	HANDLE fenceEvent = nullptr;

	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};

	//dxcCompilerを初期化
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;
	
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descriptorHeap,
		uint32_t descriptorSize, uint32_t index);

	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};

};