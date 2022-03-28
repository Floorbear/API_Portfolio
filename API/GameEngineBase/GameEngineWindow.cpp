#include "GameEngineWindow.h"

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // �����츦 �����ϰ� ��� 
        GameEngineWindow::GetInst().Off();
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
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
        MsgBoxAssert("�����츦 2�� ������ �߽��ϴ�.");
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
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ�. ȭ�鿡 ����� �� �����ϴ�.");
        return;
    }
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    //������� ���� �غ� �Ϸ�ƾ�!
    //������ �������� ���� �غ��� ���� �ִٸ� ��������!
    if (_InitFunction != nullptr)
    {
        _InitFunction();
    }

    MSG msg;

    //������ ���ο��� <MSG> ����Ʈ MessageQueue�� �ִ�.
    while (WindowOn_)
    {
        //PeekMessageA : �޼����� ������ true ������ false�� ����
        if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���⼭ ���� ���� ����
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