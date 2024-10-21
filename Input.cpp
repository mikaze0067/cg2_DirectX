#include "Input.h"
#include <cassert>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")


using namespace Microsoft::WRL;

void Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{

	HRESULT hr;

	//DirectInputの初期化
	Microsoft::WRL::ComPtr <IDirectInput8> directInput = nullptr;
	hr = DirectInput8Create(
		hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(hr));

	//キーボードデバイスの生成
	Microsoft::WRL::ComPtr <IDirectInputDevice8> keyboard = nullptr;
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(hr));

	//入力データ形式セット
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(hr));

	//排他的制御レベルのセット
	hr = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(hr));

}

void Input::Update()
{
	//キーボード情報の取得開始
	keyboard->Acquire();
	//全キーの入力状態を取得する
	BYTE key[256] = {};
	keyboard->GetDeviceState(sizeof(key), key);
	//数字の0キーが押されていたら
	if (key[DIK_0]) {
		OutputDebugStringA("Hit 0\n");
	}
}
