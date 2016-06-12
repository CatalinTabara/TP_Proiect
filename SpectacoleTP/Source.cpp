#include <windows.h>
#include "resource.h"
#define button_1		101
#define button_2		102
#define button_3		103
#define button_4		104
#define IDC_MAIN_BUTTON	105		// Button identifier
#define IDC_MAIN_EDIT	106		// Edit box identifier

HWND hEdit;
bool window1closed = false;
HINSTANCE hInst;
bool window2closed = false;
const char g_szClassName[] = "myWindowClass";
int cmd;
WNDCLASSEX wc2;
HWND b1, b2, b3, b4, c1, x;



LRESULT CALLBACK adaugare(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow2, UINT message, WPARAM wParam, LPARAM lParam);



// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{

	case WM_CREATE:
	{
					  char buff[] = "Adaugare spectacol";

					 
					  b1 = CreateWindow("BUTTON", buff, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  50, 100, 140, 100, hwnd, (HMENU)button_1, NULL, NULL);

					  b2 = CreateWindow("BUTTON", "Interval orar", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  200, 100, 140, 100, hwnd, (HMENU)button_2, NULL, NULL);

					  b3 = CreateWindow("BUTTON", "Stergere Spectacol", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  350, 100, 140, 100, hwnd, (HMENU)button_3, NULL, NULL);

					  b4 = CreateWindow("BUTTON", "Afisare Spectacole", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
						  500, 100, 140, 100, hwnd, (HMENU)button_4, NULL, NULL);
					
					  break;
	}

	case WM_CLOSE:
	{
					 DestroyWindow(hwnd);
					 break; 
	}

	case WM_DESTROY:
	{				PostQuitMessage(0);
					break; 
	}

	case WM_COMMAND:
	{
					   int wmId = LOWORD(wParam);
					   int wmEvent = HIWORD(wParam);

					   switch (wmId)
					   {
					   case button_1:
					   {
									x = (HWND)DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)adaugare);
									ShowWindow(x,10);
									UpdateWindow(x);
									/*	c1= CreateWindow(
											"EDIT",  // Predefined class; Unicode assumed 
											"Select Video's",      // Button text 
											WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
											10,         // x position 
											460,        // y position 
											100,        // Button width
											25,         // Button height
											hwnd,       // Parent window
											(HMENU)IDC_COPIL, // Assign appropriate control ID
											(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL);      // Pointer not needed.


										ShowWindow(hwnd, cmd);
										UpdateWindow(hwnd);
										//Edit box
					   
						     // Create an edit box
					  hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
						  "EDIT",
						  "",
						  WS_CHILD | WS_VISIBLE |
						  ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
						  50,
						  100,
						  200,
						  100,
						  hwnd,
						  (HMENU)IDC_MAIN_EDIT,
						  GetModuleHandle(NULL),
						  NULL);
					  HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
					  SendMessage(hEdit,
						  WM_SETFONT,
						  (WPARAM)hfDefault,
						  MAKELPARAM(FALSE, 0));
					  SendMessage(hEdit,
						  WM_SETTEXT,
						  NULL,
						  (LPARAM)"Insert text here...");

					  // Create a push button
					  HWND hWndButton = CreateWindowEx(NULL,
						  "BUTTON",
						  "OK",
						  WS_TABSTOP | WS_VISIBLE |
						  WS_CHILD | BS_DEFPUSHBUTTON,
						  50,
						  220,
						  100,
						  24,
						  hwnd,
						  (HMENU)IDC_MAIN_BUTTON,
						  GetModuleHandle(NULL),
						  NULL);
					  SendMessage(hWndButton,
						  WM_SETFONT,
						  (WPARAM)hfDefault,
						  MAKELPARAM(FALSE, 0));*/
										break;
					   }

					   case button_2:
					   {
										break;
					   }

					   case button_3:
					   {
									
					   }

					   case button_4:
					   {
										break;
					   }

					   }
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK adaugare(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDOK12)
		{
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	cmd = nCmdShow;
	bool endprogram = false;
	hInst = hInstance;
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	/*
	wc2.cbSize = sizeof(WNDCLASSEX);
	wc2.style = 0;
	wc2.lpfnWndProc = WndProc;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = hInstance;
	wc2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = g_szClassName;
	wc2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	*/

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 380,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;


	//fereastra 2

	
/*	ZeroMemory(&windowclassforwindow2, sizeof(WNDCLASSEX));
	windowclassforwindow2.cbClsExtra = NULL;
	windowclassforwindow2.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow2.cbWndExtra = NULL;
	windowclassforwindow2.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow2.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow2.hIcon = NULL;
	windowclassforwindow2.hIconSm = NULL;
	windowclassforwindow2.hInstance = hInstance;
	windowclassforwindow2.lpfnWndProc = (WNDPROC)windowprocessforwindow2;
	windowclassforwindow2.lpszClassName = "window class2";
	windowclassforwindow2.lpszMenuName = NULL;
	windowclassforwindow2.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow2))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed for window 2",
			"Window Class Failed",
			MB_ICONERROR);
	}

	HWND handleforwindow2 = CreateWindowEx(NULL,
		windowclassforwindow2.lpszClassName,
		"Child Window",
		WS_OVERLAPPEDWINDOW,
		200,
		150,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!handleforwindow2)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(handleforwindow2, nCmdShow);
	SetParent(handleforwindow2, hwnd);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (endprogram == false) {
		if (GetMessage(&msg, NULL, 0, 0));
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (window1closed == true && window2closed == true) {
			endprogram = true;
		}
	}
	MessageBox(NULL,
		"Both Windows are closed.  Program will now close.",
		"",
		MB_ICONINFORMATION);*/
	return 0;
}

LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: {
						 MessageBox(NULL,
							 "Window 2 closed",
							 "Message",
							 MB_ICONINFORMATION);

						 window2closed = true;
						 return 0;
	}
		break;
	}

	return DefWindowProc(handleforwindow, msg, wParam, lParam);
}
