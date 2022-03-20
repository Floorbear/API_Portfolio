#include <Windows.h>
#include <GameEngineContents/RockMan.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

int _stdcall WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ char* lpCmdLine,
	_In_ int	nCmdShow)
{
	GameEngine::Start<RockMan>();
	
}