﻿#include <windows.h>
#include <stdlib.h>

#include <stdexcept>

#include <tchar.h>
#include <thread>
#include <string>
#include <time.h>
#include <map>

#include "definitions.h"

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

#include "keys.h"
#include "clicks.h"
#include "init.h"
#include "keycode.h"

 int autoclick() // does the clicking
{
	while (true) {
		if (GetKeyState(keyStart) & 0x8000) { // waits for the start key to be pressed
			
			int sizeX = GetSystemMetrics(SM_CXSCREEN); // gets the screen dimentions
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

			while (true) { // calls the optional functions
				Sleep(0.01);
				if (LMB) { mouseClick(&h, &v); }
				if (RMB) { rightMouseClick(&h, &v); }
				if (BPress) { buttonPress(&keyButton); }
				if (GetKeyState(keyStop) & 0x8000) { // breaks the loop when stop keyb is pressed
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
	std::map<unsigned char, std::string> keys = create_keys();
	std::string temp_str;
	std::string key;

	switch (msg) {
	case WM_COMMAND: // iterates through possible window messages

		switch (param) {
			case RUN_MENU: // triggers when the "run" button in the dropdown menu is pressed
				MessageBeep(MB_OK);
				{
					std::thread first(autoclick);
					first.detach();
				}
				break;

			case CENTRE_CHECKBOX: // triggers if a checkbox responsible for cursor position is changed
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

			case LMB_CLICK: // triggers if a checkbox responsible for left clicks is changed
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

			case RMB_CLICK:// triggers if a checkbox responsible for right clicks is changed
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

			case KEYBOARD_PRESS:// triggers if a checkbox responsible for keyboard button press is changed (needs an update to a newer system)
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

			case REP_CLICK: // triggers if a checkbox responsible for repeated clicks is changed
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
			
			case START_BUTTON: // triggers upon clicking the "start button" button. Sets the keybind for starting the loop
				
				keyStart = Keycode();

				temp_str = "Start button: ";
				try {
					key = keys.at(keyStart);
					temp_str.append(key);
				}
				catch(const std::out_of_range& e){ // catches trying to enter an invalid/broken character (sometimes triggers on ctrl/alt/shift for reasons unknown)
					temp_str.append("Unknown");
				}

				SetWindowText(hStart, temp_str.c_str());
				break;

			case STOP_BUTTON: // triggers upon clicking the "stop button" button. Sets the keybind for stopping the loop

				keyStop = Keycode();

				temp_str = "Stop button: ";

				try {
					key = keys.at(keyStop);
					temp_str.append(key);
				}
				catch (const std::out_of_range& e) { // catches trying to enter an invalid/broken character (sometimes triggers on ctrl/alt/shift for reasons unknown)
					temp_str.append("Unknown");
				}

				SetWindowText(hStop, temp_str.c_str());
				break;

			case PRESS_BUTTON: // triggers upon clicking the "Set button" button. Sets the keybind for stopping the loop

				keyButton = Keycode();

				temp_str = "Button: ";

				try {
					key = keys.at(keyButton);
					temp_str.append(key);
				}
				catch (const std::out_of_range& e) { // catches trying to enter an invalid/broken character (sometimes triggers on ctrl/alt/shift for reasons unknown)
					temp_str.append("Unknown");
				}

				SetWindowText(hLetter, temp_str.c_str());
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


