#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow()
    :hInst_(nullptr)
    ,hWnd_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
} 

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    //윈도우 클래스 등록
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst_;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExW(&wcex);
}

void GameEngineWindow::ShowGameWindow()
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        return;
    }
    ShowWindow(hWnd_, SW_MAXIMIZE);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::CreatGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

	hWnd_ = CreateWindowExA(0L,"GameEngineWindowClass",_Title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

	if (!hWnd_)
	{
		return;
	}
}
