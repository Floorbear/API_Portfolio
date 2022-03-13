#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstace,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int	nCmdShow)
{

	GameEngineDebug::LeakCheckOn();
	//GameEngineBase�� cpp���� �˱��� ����
	GameEngineWindow::GetInst().CreatGameWindow(hInstace,"GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();

	while (true)
	{
	}
}