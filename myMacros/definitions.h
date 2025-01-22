#pragma once

/*
* element mapping
*/
#define RUN_MENU 1
#define CENTRE_CHECKBOX 2
#define LMB_CLICK 3
#define KEYBOARD_PRESS 4
#define REP_CLICK 5
#define START_BUTTON 6
#define STOP_BUTTON 7
#define RMB_CLICK 8
#define PRESS_BUTTON 9

// definitions
#define MAX_INPUT 4096 // maximum input length
#define WINDOW_SIZE_X 500 // application window width
#define WINDOW_SIZE_Y 500 // application window height
#define MENU_GAP 30 // gap between menu options

class System{	// Class definition for various parameters
	public:
		bool center;
		bool LMB;
		bool RMB;
		bool bPress;
		bool isRep;
		bool status;

		char keyStart;
		char keyStop;
		char keyButton;
		System(){
			center = true;
			LMB = false;
			RMB = false;
			bPress = false;
			isRep = false;
			status = 0;

			keyStart = 'C';
			keyStop = 'V';
			keyButton = 'W';
		}
};


System sys;

HMENU hMenu;
HWND hHoriz;
HWND hVert;
HWND hLetter;
HWND hTick;
HWND hStart;
HWND hStop;

