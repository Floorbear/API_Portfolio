#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineDebug.h"

class GameEngineWindow
{
private:
	static GameEngineWindow* Inst_;
public:
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_;
	}

	static void Destory()
	{
		if (Inst_ != nullptr)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void RegClass(HINSTANCE _HInst);
	void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title);
	void ShowGameWindow();
	void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());
	void Off();

protected:
private:
	HWND hWnd_;
	HINSTANCE hInst_;
	std::string Title_;
	HDC HDC_;
	bool WindowOn_;

	GameEngineWindow();
	~GameEngineWindow();
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(const GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Ohter) = delete;
	GameEngineWindow& operator=(const GameEngineWindow&& _Other) noexcept = delete;
};

