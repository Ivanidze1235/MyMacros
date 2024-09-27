#include <windows.h>
#include <stdlib.h>

#include <tchar.h>
#include <thread>
#include <string>
#include <time.h>
#include <map>
#include "keys.h"


using namespace std;

/*
* maps the buttons
*/
#define RUN_MENU 1
#define CENTRE_CHECKBOX 2
#define LMB_CLICK 3
#define KEYBOARD_PRESS 4
#define REP_CLICK 5
#define START_BUTTON 6
#define STOP_BUTTON 7

// definitions
#define MAX_INPUT 4096 // maximum input length
#define WINDOW_SIZE_X 500
#define WINDOW_SIZE_Y 500
#define MENU_GAP 30 // gap between menu options


bool Center = true;
bool LMB = false;
bool BPress = false;
bool isRep = false;

char keyStart = 'C';
char keyStop = 'V';

void mouseClick(int PosX, int PosY);

void buttonPress(char letter) // presses a keyboard letter button when called
{
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

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

HMENU hMenu;
HWND hHoriz;
HWND hVert;
HWND hLetter;
HWND hTick;
HWND hStart;
HWND hStop;


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
	CreateWindow("Static", "Horizontal(px):", WS_VISIBLE | WS_CHILD, 10/*margin x*/, MENU_GAP/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hHoriz = CreateWindow("Edit", "100", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, MENU_GAP * 2/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	
	CreateWindow("Static", "Vertical(px):", WS_VISIBLE | WS_CHILD, 10/*margin x*/, MENU_GAP * 3/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hVert = CreateWindow("Edit", "100", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, MENU_GAP * 4/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	
	CreateWindow("Static", "keyboard letter:", WS_VISIBLE | WS_CHILD, 10/*margin x*/, MENU_GAP * 5/*margin y*/, 150/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hLetter = CreateWindow("Edit", "w", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, MENU_GAP * 6/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	
	CreateWindow("Static", "Tickrate:", WS_VISIBLE | WS_CHILD, 10/*margin x*/, MENU_GAP * 7/*margin y*/, 150/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);
	hTick = CreateWindow("Edit", "10", WS_VISIBLE | WS_CHILD | WS_BORDER, 10/*margin x*/, MENU_GAP * 8/*margin y*/, 100/*x*/, 20/*y*/, hwnd, NULL, NULL, NULL);

	hStart = CreateWindow("STATIC", "C", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, MENU_GAP * 9, 100, 40, hwnd, NULL, NULL, NULL);
	hStop = CreateWindow("STATIC", "V", WS_VISIBLE | WS_CHILD | SS_LEFT, 220, MENU_GAP * 9, 100, 40, hwnd, NULL, NULL, NULL);


	CreateWindow(TEXT("BUTTON"), TEXT("Set Start Key"),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, MENU_GAP * 11, 185, 35,
		hwnd, (HMENU)START_BUTTON, NULL, NULL);

	CreateWindow(TEXT("BUTTON"), TEXT("Set Stop Key"),
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		220, MENU_GAP * 11, 185, 35,
		hwnd, (HMENU)STOP_BUTTON, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("cursor in center"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP, 185, 35,
		hwnd, (HMENU)CENTRE_CHECKBOX, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("LMB click"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 2, 185, 35,
		hwnd, (HMENU)LMB_CLICK, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("press button"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 3, 185, 35,
		hwnd, (HMENU)KEYBOARD_PRESS, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("repeated clicks"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 4, 185, 35,
		hwnd, (HMENU)REP_CLICK, NULL, NULL);
}

 int autoclick() // does the clicking
{
	while (true) {
		if (GetKeyState(keyStart) & 0x8000) {
			
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
				char horisontal[MAX_INPUT];
				GetWindowText(hHoriz, horisontal, MAX_INPUT);
				char vertical[MAX_INPUT];
				GetWindowText(hVert, vertical, MAX_INPUT);
				h = atoi(horisontal);
				v = atoi(vertical);
			}
			char symb[2];
			GetWindowText(hLetter, symb, 2);

			while (true) {
				Sleep(0);
				if (LMB) { mouseClick(h, v); }
				if (BPress) { buttonPress(symb[0]); }
				if (GetKeyState(keyStop) & 0x8000) {
					return 0;
				}
			}
			
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
		WINDOW_SIZE_X, WINDOW_SIZE_Y,						// Window size
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

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) { // processes windows messages

	BOOL checked;
	int i;
	std::map<char, std::string> keys = create_keys();
	std::string temp_str;
	std::string key;

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
			
			case START_BUTTON:
				i = 0;
				while (i < 100000) {
					// iterates through all possible key codes
					for (int keyCode = 0; keyCode < 256; ++keyCode) {

						if (GetAsyncKeyState(keyCode) & 0x8000) {
							keyStart = static_cast<char>(keyCode);
							break;
						}
					}
					i++;
					Sleep(0.1);
				}
				
				temp_str = "Start button: ";
				
				if (keyStart >= 65 && keyStart <= 90) {
					temp_str.push_back(keyStart);
				}
				else {
					std::string key = keys.at(keyStart);
					temp_str.append(key);
				}
				
				SetWindowText(hStart, temp_str.c_str());
				break;

			case STOP_BUTTON:
				i = 0;
				while (i < 100000) {
					// iterates through all possible key codes
					for (int keyCode = 0; keyCode < 256; ++keyCode) {

						if (GetAsyncKeyState(keyCode) & 0x8000) {
							keyStop = static_cast<char>(keyCode);
							break;
						}
					}
					i++;
					Sleep(0.1);
				}

				temp_str = "Stop button: ";
				if (keyStop >= 65 && keyStop <= 90) {
					temp_str.push_back(keyStop);
				}
				else {
					std::string key = keys.at(keyStop);
					temp_str.append(key);
				}
				SetWindowText(hStop, temp_str.c_str());
				break;

		}
		break;
	case WM_CREATE: // called on window creation
		AddMenus(hwnd);
		AddControls(hwnd);
		CheckDlgButton(hwnd, CENTRE_CHECKBOX, BST_CHECKED);
		break;
	case WM_DESTROY: // called on window destruction
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
		
	}
}

void mouseClick(int PosX, int PosY) // left-clicks every set amount of time
{

	SetCursorPos(PosX, PosY);
	INPUT mouseInput = { 0 };
	mouseInput.type = INPUT_MOUSE;
	mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseInput, sizeof(mouseInput));
	mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseInput, sizeof(mouseInput));
	ZeroMemory(&mouseInput, sizeof(mouseInput));
	int tick;
	char timer[MAX_INPUT];
	GetWindowText(hTick, timer, MAX_INPUT);
	tick = atoi(timer);
	Sleep(tick);
}
