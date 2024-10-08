#pragma once

void mouseClick(int* PosX, int* PosY) // left-clicks every set amount of time
{

	SetCursorPos(*PosX, *PosY);
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

void rightMouseClick(int* PosX, int* PosY) // right-clicks every set amount of time
{

	SetCursorPos(*PosX, *PosY);
	INPUT mouseInput = { 0 };
	mouseInput.type = INPUT_MOUSE;
	mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouseInput, sizeof(mouseInput));
	mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouseInput, sizeof(mouseInput));
	ZeroMemory(&mouseInput, sizeof(mouseInput));
	int tick;
	char timer[MAX_INPUT];
	GetWindowText(hTick, timer, MAX_INPUT);
	tick = atoi(timer);
	Sleep(tick);
}

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