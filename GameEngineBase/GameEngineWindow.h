#pragma once
#include <Windows.h>
#include <string>


class GameEngineWindow
{
private:
	static GameEngineWindow* Inst_;
	HINSTANCE hInst_;
	HWND hWnd_;
	std::string Title_;

public:
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_;
	}

	static void Destory()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	void RegClass(HINSTANCE _hInst);
	void CreatGameWindow(HINSTANCE _hInst,const std::string& _Title);
	void ShowGameWindow();


protected:

private:
	GameEngineWindow();
	~GameEngineWindow();

	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(const GameEngineWindow&& _Other) = delete;
};

