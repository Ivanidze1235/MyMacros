#include <windows.h>
#include <stdlib.h>

#include <tchar.h>
#include <thread>
#include <string>
#include <time.h>
#include <map>

#include "definitions.h"

bool Center = true;
bool LMB = false;
bool RMB = false;
bool BPress = false;
bool isRep = false;

char keyStart = 'C';
char keyStop = 'V';

void buttonPress(char* letter) // presses a keyboard letter button when called
{
	INPUT kbInput = { 0 };
	kbInput.type = INPUT_KEYBOARD;
	kbInput.ki.wVk = VkKeyScan(*letter);
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


#include "keys.h"
#include "clicks.h"
#include "init.h"


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
				Sleep(0.01);
				if (LMB) { mouseClick(&h, &v); }
				if (RMB) { rightMouseClick(&h, &v); }
				if (BPress) { buttonPress(&symb[0]); }
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
	BOOL key_found = false;
	std::map<unsigned char, std::string> keys = create_keys();
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

			case RMB_CLICK:
				checked = IsDlgButtonChecked(hwnd, RMB_CLICK);

				if (checked) {
					CheckDlgButton(hwnd, RMB_CLICK, BST_UNCHECKED);
					RMB = false;
				}
				else {
					CheckDlgButton(hwnd, RMB_CLICK, BST_CHECKED);
					RMB = true;
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
				key_found = false;

				while (!key_found) {
					// iterates through all possible key codes
					for (int keyCode = 0; keyCode < 256; ++keyCode) {

						if (GetAsyncKeyState(keyCode) & 0x8000) {
							keyStart = static_cast<unsigned char>(keyCode);
							key_found = true;
							break;
						}
					}
					Sleep(0.1);
				}

				temp_str = "Start button: ";
				
				if (keys.count(keyStart) > 0) {
					key = keys.at(keyStart);
					temp_str.append(key);
				}

				else {
					temp_str.append("Unknown");
				}

				SetWindowText(hStart, temp_str.c_str());
				break;

			case STOP_BUTTON:

				while (!key_found) {
					// iterates through all possible key codes
					for (int keyCode = 0; keyCode < 256; ++keyCode) {

						if (GetAsyncKeyState(keyCode) & 0x8000) {
							keyStop = static_cast<unsigned char>(keyCode);
							key_found = true;
							break;
						}
					}
					Sleep(0.1);
				}

				temp_str = "Stop button: ";

				if (keys.count(keyStop) > 0) {
					key = keys.at(keyStop);
					temp_str.append(key);
				}

				else {
					temp_str.append("Unknown");
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


