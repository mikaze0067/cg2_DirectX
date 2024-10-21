#pragma once
#include <windows.h>
#include <wrl.h>

using namespace Microsoft::WRL;


//入力
class Input {
public: //メンバ変数
	

	template<class T> using Comptr = Microsoft::WRL::ComPtr<T>;

	//初期化
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	//更新
	void Update();

};