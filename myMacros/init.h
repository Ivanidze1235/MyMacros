#pragma once

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

	CreateWindow(TEXT("button"), TEXT("RMB click"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 3, 185, 35,
		hwnd, (HMENU)RMB_CLICK, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("press button"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 4, 185, 35,
		hwnd, (HMENU)KEYBOARD_PRESS, NULL, NULL);

	CreateWindow(TEXT("button"), TEXT("repeated clicks"),
		WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		220, MENU_GAP * 5, 185, 35,
		hwnd, (HMENU)REP_CLICK, NULL, NULL);
}