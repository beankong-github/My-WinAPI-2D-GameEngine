﻿// WinAPIStudy.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "pch.h"
#include "framework.h"
#include "WinAPIStudy.h"
#include "CPlayer.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE g_hInst;            
HWND g_hWnd;
CPlayer g_player;

UINT uiSwitch = 0;

                                                                
ATOM                MyRegisterClass(HINSTANCE hInstance);       
BOOL                InitInstance(HINSTANCE, int);               
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);        
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);          

int APIENTRY wWinMain( HINSTANCE hInstance,                     
                       HINSTANCE hPrevInstance,                 
                       LPWSTR    lpCmdLine,                     
                       int       nCmdShow)                   
{
    // 생성시킬 윈도우 설정
    MyRegisterClass(hInstance);

    // 플레이어 초기화
    g_player.SetPos(POINT{ 250, 200 });
    g_player.SetScale(POINT{ 50, 50 });

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        // 초기화가 안되면 메인에서 탈출
        return FALSE;
    }

    // 단축키 정보들
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPISTUDY));     // Accle Table 정보에 저장된 단축키 정보를 가져옴

    // 메세지 구조체
    MSG msg = {};

    // 메세지 기반 타이머 생성
    // 아이디가 0인 Timer 생성 (이벤트 간격은 1초(1000))
    // => 1초 간격으로 WM_TIMER 이벤트 발생
    SetTimer(g_hWnd, 0, 1000, nullptr); 

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))                      // 메세지 큐에 쌓여 있는 메세지를 msg에 하나씩 가져온다, nullptr을 전달할 경우 스레드에 속하는 모든 창에 대한 메세지를 가져온다, 나머지 두 정수는 메세지 필터링 용이다.
    {

        // 메세지 처리
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))  // 액셀러레이터(조합키 첫번째 요소)가 입력되었을 경우 TranslateMessage, DispatchMessage 함수가 실행되지 못하도록 막아 버리며 다음번의 WM_COMMAND메시지가 처리되도록 해 준다. 물론 액셀러레이터 입력이 아니면 FALSE를 리턴하여 다른 메시지들은 정상적으로 처리되도록 해 준다.
        {
            TranslateMessage(&msg);                              // 키 입력을 문자로 전환하여 메세지 큐에 저장한다
            DispatchMessage(&msg);                               // 창 프로시저에 메세지를 처리하도록 전달. 일반적으로 GetMessage 함수에 의해 검색된 메세지를 발송하는데 사용
        }
    }

    // 타이머 삭제
    KillTimer(g_hWnd, 0);

    return (int) msg.wParam;                                     // 메세지에 대한 부가 정보
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;       // 윈도우 설정값들을 모아놓은 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;      // 해당 윈도우 이벤트 처리 함수 주소
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPISTUDY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = L"MyWin";     // 윈도우 설정값의 이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance;

   g_hWnd = CreateWindowW(L"MyWin", L"MyWindow", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   // 윈도우 보이기
   ShowWindow(g_hWnd, TRUE);
   UpdateWindow(g_hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
          
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);    // WM_QUIT 발생
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // dc(device context) : rendering 관련된 데이터 집합 (ex: pen - 그리기, brush - 채우기, bitmap - window에서 상단바를 제외한 배경)

            // 펜 생성 
            HPEN newPen = CreatePen(PS_ALTERNATE, 3, RGB(255, 0, 255));

            // 브러쉬 생성
            HBRUSH newBrush = CreateSolidBrush(RGB(0, 0, 255));

            // 새 도구를 장착하고 기존의 도구를 저장해둠
            HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
            HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
            
            // Player 그리기
            POINT ptPos = g_player.GetPos();
            POINT ptScale = g_player.GetScale();

            Rectangle(hdc, (ptPos.x - (ptScale.x / 2)),     // left 
                           (ptPos.y - (ptScale.y / 2)),     // top
                           (ptPos.x + (ptScale.x / 2)),     // right
                           (ptPos.y + (ptScale.y / 2)));    // bottom

            // 기존 도구로 되돌려놓기
            SelectObject(hdc, prevBrush);
            SelectObject(hdc, prevPen);

            // 사용이 끝난 도구 삭제하기
            DeleteObject(newBrush);
            DeleteObject(newPen);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
        // 왼쪽 방향키 누르면 프레임마다 왼쪽으로 1씩 이동
        if (VK_LEFT == wParam)
        {
            uiSwitch = 0;
        }

        // 오른쪽 방향키 누르면 프레임마다 오른쪽으로 1씩 이동
        if (VK_RIGHT == wParam)
        {
            uiSwitch = 1;
        }
        break;

    case WM_TIMER:
        POINT ptPos = g_player.GetPos();

        if (uiSwitch)
            ptPos.x += 10;
        else
            ptPos.x -= 10;

        g_player.SetPos(ptPos);

        // 화면을 무효화 영역으로 설정 -> 후에 WM_PAINT 호출됨
        InvalidateRect(g_hWnd, nullptr, true);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
