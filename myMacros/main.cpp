#include <windows.h>
#include <stdlib.h>

#include <tchar.h>
#include <thread>
#include <string>
#include <time.h>
using namespace std;

/*
* maps the buttons
*/
#define RUN_MENU 1
#define CENTRE_CHECKBOX 2
#define LMB_CLICK 3
#define KEYBOARD_PRESS 4
#define REP_CLICK 5


bool Center = false;
bool LMB = false;
bool BPress = false;
bool isRep = false;

void mouseClick(int PosX, int PosY, bool click);

void buttonPress(char letter, bool press) // presses a keyboard letter button when called
{
	if (press) {
		INPUT kbInput = { 0 };
		kbInput.type = INPUT_KEYBOARD;
		kbInput.ki.wVk = VkKeyScan(letter);
		SendInput(1, &kbInput, sizeof(kbInput));
		ZeroMemory(&kbInput, sizeof(kbInput));
		if (isRep) {
			kbInput.ki.wVk = VK_UP;
			SendInput(1, &kbInput, sizeof(kbInput));
		}
		
	}
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

HMENU hMenu;
HWND hHoriz;
HWND hVert;
HWND hLetter;
HWND hTick;


void AddMenus(HWND hwnd) // creates a dropdown menu
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	

	AppendMenu(hFileMenu, MF_STRING, RUN_MENU, "run");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "Options");

	SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd) // creates inputs for customizable variables
{
	CreateWindow("Static", "Horizontal(px):", WS_VISIBLE | WS_CHILD, 10/*margin x*/, 10/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hHoriz = CreateWindow("Edit", "100", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, 30/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	CreateWindow("Static", "Vertical(px):", WS_VISIBLE | WS_CHILD, 10/*margin x*/, 70/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hVert = CreateWindow("Edit", "100", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, 90/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	CreateWindow("Static", "keyboard letter:", WS_VISIBLE | WS_CHILD, 10/*margin x*/, 120/*margin y*/, 150/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hLetter = CreateWindow("Edit", "w", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, 150/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	CreateWindow("Static", "Tickrate:", WS_VISIBLE | WS_CHILD, 10/*margin x*/, 180/*margin y*/, 150/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hTick = CreateWindow("Edit", "10", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, 210/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);


	CreateWindow("Static", "options->run to initiate;  C to start;  F4 to stop;  F3 to leave the loop.", WS_VISIBLE | WS_CHILD, 10/*margin x*/, 240/*margin y*/, 300/*x*/, 50/*y*/, hwnd, NULL, NULL, NULL);
	
	CreateWindow(TEXT("button"), TEXT("cursor in center"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, 10, 185, 35,
		hwnd, (HMENU)CENTRE_CHECKBOX, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("LMB click"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, 40, 185, 35,
		hwnd, (HMENU)LMB_CLICK, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("press button"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, 70, 185, 35,
		hwnd, (HMENU)KEYBOARD_PRESS, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("repeated clicks"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, 100, 185, 35,
		hwnd, (HMENU)REP_CLICK, NULL, NULL);
}



 int autoclick() // does the clicking
{
	while (true) {
		if (GetAsyncKeyState('C') & 0x8000) {
			int sizeX = GetSystemMetrics(SM_CXSCREEN);
			int sizeY = GetSystemMetrics(SM_CYSCREEN);
			
			int h;
			int v;
			
			if (Center == true)
			{
				h = sizeX/2;
				v = sizeY/2;
			}
			else
			{
				char horisontal[10000];
				GetWindowText(hHoriz, horisontal, 10000);
				char vertical[10000];
				GetWindowText(hVert, vertical, 10000);
				h = atoi(horisontal);
				v = atoi(vertical);
			}
			char symb[2];
			GetWindowText(hLetter, symb, 2);
			
			while (true) {
				mouseClick(h, v, LMB);
				buttonPress(symb[0], BPress);
				if (GetKeyState(VK_F4) & 0x8000) {
					break;
				}
				
			}
		}

		if (GetKeyState(VK_F3) & 0x8000) {
			break;
		}
	}
	return 0;
	
}

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) { // creates the window
	// Register the window class
	const char* CLASS_NAME = "myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	// Create the window
	CreateWindow(CLASS_NAME, "My Macros",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,			// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,				// Window initial position
		500, 400,						// Window size
		nullptr, nullptr, nullptr, nullptr);
	

	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) { // creates elements of the window

	
	BOOL checked;
	switch (msg) {
	case WM_COMMAND:
		 
		switch (param) {
			case RUN_MENU:
				MessageBeep(MB_OK);
				{
					std::thread first(autoclick);
					first.detach();
				}
				break;

			case CENTRE_CHECKBOX:
				checked = IsDlgButtonChecked(hwnd, CENTRE_CHECKBOX);

				if (checked) {
					CheckDlgButton(hwnd, CENTRE_CHECKBOX, BST_UNCHECKED);
					Center = false;
				}
				else {
					CheckDlgButton(hwnd, CENTRE_CHECKBOX, BST_CHECKED);
					Center = true;
				}
				break;

			case LMB_CLICK:
				checked = IsDlgButtonChecked(hwnd, LMB_CLICK);

				if (checked) {
					CheckDlgButton(hwnd, LMB_CLICK, BST_UNCHECKED);
					LMB = false;
				}
				else {
					CheckDlgButton(hwnd, LMB_CLICK, BST_CHECKED);
					LMB = true;
				}
				break;

			case KEYBOARD_PRESS:
				checked = IsDlgButtonChecked(hwnd, KEYBOARD_PRESS);

				if (checked) {
					CheckDlgButton(hwnd, KEYBOARD_PRESS, BST_UNCHECKED);
					BPress = false;
				}
				else {
					CheckDlgButton(hwnd, KEYBOARD_PRESS, BST_CHECKED);
					BPress = true;
				}
				break;

			case REP_CLICK:
				checked = IsDlgButtonChecked(hwnd, REP_CLICK);

				if (checked) {
					CheckDlgButton(hwnd, REP_CLICK, BST_UNCHECKED);
					isRep = false;
				}
				else {
					CheckDlgButton(hwnd, REP_CLICK, BST_CHECKED);
					isRep = true;
				}
				break;
		}
		break;
	case WM_CREATE:
		AddMenus(hwnd);
		AddControls(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
		
	}
}

void mouseClick(int PosX, int PosY, bool click) // left-clicks every set amount of time
{

	SetCursorPos(PosX, PosY);
	if (click) {
		INPUT mouseInput = { 0 };
		mouseInput.type = INPUT_MOUSE;
		mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &mouseInput, sizeof(mouseInput));
		mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &mouseInput, sizeof(mouseInput));
		ZeroMemory(&mouseInput, sizeof(mouseInput));

		int tick;
		char timer[100000];
		GetWindowText(hTick, timer, 100000);
		tick = atoi(timer);
		Sleep(tick);
	}

}