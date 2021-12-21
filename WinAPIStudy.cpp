﻿// WinAPIStudy.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPIStudy.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다. (프로그램 시작 주소)
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 전방 선언:
ATOM                MyRegisterClass(HINSTANCE hInstance);       // 창의 속성 설정하고(윈도우 설정하는 구조체 설정) 해당 창의 클래스를 메모리에 등록한다 (ATOM - Access to Memory)
BOOL                InitInstance(HINSTANCE, int);               // 창 초기화 및 창 보이기
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);        // 창의 메세지 처리 (CALLBACK - _stdcall // 함수 호출 규약)
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);          // 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                 // 프로그램 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance,          // 이전 시작 주소 (현재는 가상 메모리 시스템으로 한 프로그램이 메모리에 단독으로 들어간 것처럼 사용되기 때문에 필요 x)
                     _In_ LPWSTR    lpCmdLine,                  // 프로그램 실행 cmd 명령어, 이것을 이용해 한 프로그램에 여러 실행 버전을 만들 수 있음 (예를 들어 개발자 모드)
                     _In_ int       nCmdShow)                   // 윈도우가 처음 실행될 때 어떤 화면의 형태를 가질지 (ex 최대화 상태, 최소화 상태) 
{
    // 참고하지 않은 인수들 //
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 리소스 파일의 스트링 테이블에서 문자열을 가져와서 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);             // 윈도우 인스턴스(시작 주소), 스트링 테이블 ID, 문자열을 가져오고자 하는 변수, 문자열의 길이
    LoadStringW(hInstance, IDC_WINAPISTUDY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);                                                 // 창의 속성 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        // 초기화가 안되면 메인에서 탈출
        return FALSE;
    }


    // 단축키 정보들
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPISTUDY));     // Accle Table 정보에 저장된 단축키 정보를 가져옴

    // 메세지
    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))         // 메세지 큐에 쌓여 있는 메세지를 msg에 하나씩 가져온다, nullptr을 전달할 경우 스레드에 속하는 모든 창에 대한 메세지를 가져온다, 나머지 두 정수는 메세지 필터링 용이다.
    {
        // 만약 GetMessage에서 가져온 메세지가 WM_QUIT 인 경우 false를 반환한다.
        // 메세지가 없는 경우나 다른 메세지가 있는 경우는 true이기 때문에 계속 while 문을 돈다.
        // MW_QUIT 메세지는 윈도우가 종료될 때 발생한다.

        // 메세지 처리
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 액셀러레이터(조합키 첫번째 요소)가 입력되었을 경우 TranslateMessage, DispatchMessage 함수가 실행되지 못하도록 막아 버리며 다음번의 WM_COMMAND메시지가 처리되도록 해 준다. 물론 액셀러레이터 입력이 아니면 FALSE를 리턴하여 다른 메시지들은 정상적으로 처리되도록 해 준다.
        {
            TranslateMessage(&msg);     // 키 입력을 문자로 전환하여 메세지 큐에 저장한다
            DispatchMessage(&msg);      // 창 프로시저에 메세지를 전달. 일반적으로 GetMessage 함수에 의해 검색된 메세지를 발송하는데 사용
        }
    }

    return (int) msg.wParam;    // 메세지에 대한 부가 정보
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPISTUDY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPISTUDY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
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
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);    // WM_QUIT 발생
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:                                                      // 최초로 창을 띄울때, 최대화 또는 최소화 할 때 등은 자동으로 WM_PAINT 메세지가 발생한다.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
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
