#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstace,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int	nCmdShow)
{

	GameEngineDebug::LeakCheckOn();
	//GameEngineBase의 cpp까지 알길이 없음
	GameEngineWindow::GetInst().CreatGameWindow(hInstace,"GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();

	while (true)
	{
	}
}