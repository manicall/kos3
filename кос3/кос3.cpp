// кос3.cpp : Определяет точку входа для приложения.
//
#undef UNICODE
#include "framework.h"
#include "кос3.h"
#include <string>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK   PviewDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3));

    DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), 0, PviewDlgProc);

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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


HDC hdc;
PAINTSTRUCT ps; // структура для перерисовки окна
HWND hEdit;
HWND hList;
HWND hCombo;
std::string text;
//Процедура обработки сообщений диалогового окна
BOOL CALLBACK   PviewDlgProc(HWND    hDlg,
    UINT    wMsg,
    WPARAM  wParam,
    LPARAM  lParam)
{
    switch (wMsg)
    {
    // сообщение об инициализации диалоговой формы
    case WM_INITDIALOG:
        hEdit =  GetDlgItem(hDlg, IDC_EDIT1);
        hList =  GetDlgItem(hDlg, IDC_LIST1);
        hCombo = GetDlgItem(hDlg, IDC_COMBO1);
        break;

    case WM_CLOSE:
        PostQuitMessage(0);
        break;


    case WM_PAINT:
        hdc = BeginPaint(hDlg, &ps);

        EndPaint(hDlg, &ps);
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) { // срабатывает при вводе текста в edit control
            SendMessage(hEdit, WM_GETTEXT, 200, (LPARAM)text.c_str());
            SendMessage(hList, LB_ADDSTRING, strlen(text.c_str()), (LPARAM)text.c_str());
            SendMessage(hCombo, CB_ADDSTRING, strlen(text.c_str()), (LPARAM)text.c_str());
            SendMessage(hCombo, WM_SETTEXT, strlen(text.c_str()), (LPARAM)text.c_str());
        }
        switch (LOWORD(wParam))
        {
        // обработка меню программы по итендификаторам
        case ID_32771:  MessageBox(0, "первый уровень: пункт меню 1\n второй уровень: пункт меню 1", "сообщение", 0); break;
        case ID_32772:  MessageBox(0, "первый уровень: пункт меню 1\n второй уровень: пункт меню 2", "сообщение", 0); break;
        case ID_32773:  MessageBox(0, "первый уровень: пункт меню 2\n второй уровень: пункт меню 1", "сообщение", 0); break;
        case ID_32774:  MessageBox(0, "первый уровень: пункт меню 2\n второй уровень: пункт меню 2", "сообщение", 0); break;
        // обработка кнопок
        case IDC_BUTTON1:
            MessageBox(0, "кнопка1", "сообщение", 0);
            break;
        case IDC_BUTTON2:
            MessageBox(0, "кнопка2", "сообщение", 0);
            break;
        case IDC_BUTTON3:
            MessageBox(0, "кнопка3", "сообщение", 0);
            break;
        default:
            return FALSE;
        }
        break;

    default:
        return FALSE;
    }

    return TRUE;
}
