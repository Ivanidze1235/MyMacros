#pragma once

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
#define RMB_CLICK 8

// definitions
#define MAX_INPUT 4096 // maximum input length
#define WINDOW_SIZE_X 500
#define WINDOW_SIZE_Y 500
#define MENU_GAP 30 // gap between menu options

bool Center = true;
bool LMB = false;
bool RMB = false;
bool BPress = false;
bool isRep = false;

char keyStart = 'C';
char keyStop = 'V';

HMENU hMenu;
HWND hHoriz;
HWND hVert;
HWND hLetter;
HWND hTick;
HWND hStart;
HWND hStop;
