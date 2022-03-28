#include "GameEngineWindow.h"

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // 윈도우를 종료하고 모든 
        GameEngineWindow::GetInst().Off();
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    RECT Rc = { 0,0,_Scale.ix(),_Scale.iy() };

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);
}
void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    if (hInst_ != nullptr)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        return;
    }

    hInst_ = _hInst;
    Title_ = _Title;
    RegClass(_hInst);
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}
void GameEngineWindow::ShowGameWindow()
{
    if (hWnd_ == nullptr)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        return;
    }
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    //윈도우는 전부 준비가 완료됐어!
    //루프를 돌기전에 뭔가 준비할 것이 있다면 실행해줘!
    if (_InitFunction != nullptr)
    {
        _InitFunction();
    }

    MSG msg;

    //윈도우 내부에는 <MSG> 리스트 MessageQueue가 있다.
    while (WindowOn_)
    {
        //PeekMessageA : 메세지가 있으면 true 없으면 false를 리턴
        if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //여기서 부터 게임 로직
        if (_LoopFunction == nullptr)
        {
            continue;
        }

        _LoopFunction();
    }
    
}
void GameEngineWindow::Off()
{
    WindowOn_ = false;
}
GameEngineWindow::GameEngineWindow()
    :   hInst_(nullptr)
    ,   hWnd_(nullptr)
    ,   WindowOn_(true)
    ,   HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (HDC_ != nullptr)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }
    if (hWnd_ != nullptr)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}