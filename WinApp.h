#pragma once
#include <Windows.h>
#include <cstdint>


//WindowAPI
class WinApp {
public:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM LPARAM);

	
public:

	//初期化
	void Initialize();
	//更新
	void Update();

	void Finalize();

	//getter
	HWND GetHwnd()const { return hwnd; }

	//getter
	HINSTANCE GetHInstance()const { return wc.hInstance; }

	//クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;
private:
	HWND hwnd = nullptr;

	//ウィンドウクラスの設定
	WNDCLASS wc{};
};