#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800    //DirectInputのバージョン
#include <dinput.h>
#include "WinApp.h"

using namespace Microsoft::WRL;

//入力
class Input {
public: //メンバ変数

	template<class T> using Comptr = Microsoft::WRL::ComPtr<T>;

public: //メンバ変数

	//初期化
	void Initialize(WinApp*winApp);
	//更新
	void Update();

	bool PushKey(BYTE keyNumber);

	bool TriggerKey(BYTE keyNumber);

private:
	//DirectInputの初期化
	ComPtr <IDirectInput8> directInput;
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	//全キーの状態
	BYTE key[256] = {};
	//旋回の全キーの状態
	BYTE keyPre[256] = {};
	//WindowAPI
	WinApp* winApp_ = nullptr;
};