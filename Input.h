#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800    //DirectInputのバージョン
#include <dinput.h>


//入力
class Input {
public: //メンバ変数

	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();

private:
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
};