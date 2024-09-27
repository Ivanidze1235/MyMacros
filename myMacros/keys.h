#pragma once
#include <map>
#include <string>

std::map<char, std::string> create_keys() {
	std::map<char, std::string> keys;
	
	keys[-69] = "=";
	keys[-65] = "/";
	keys[-64] = "'";
	keys[-36] = "\\";
	keys[-34] = "#";
	keys[-33] = "`";
	keys[1] = "Mouse1";
	keys[2] = "Mouse2";
	keys[4] = "Mouse3";
	keys[5] = "Mouse4";
	keys[6] = "Mouse5";
	keys[8] = "Backspace";
	keys[9] = "Tab";
	keys[16] = "Shift";
	keys[17] = "Ctrl";
	keys[18] = "Alt";
	keys[19] = "Brk";
	keys[20] = "Caps Lock";
	keys[27] = "Esc";
	keys[32] = "Spacebar";
	keys[33] = "PageUp";
	keys[34] = "PageDown";
	keys[35] = "End";
	keys[36] = "Home";
	keys[37] = "ArrowLeft";
	keys[38] = "ArrowUp";
	keys[39] = "ArrowRight";
	keys[40] = "ArrowDown";
	keys[44] = "PrintScreen";
	keys[46] = "Delete";
	keys[48] = "0";
	keys[49] = "1";
	keys[50] = "2";
	keys[51] = "3";
	keys[52] = "4";
	keys[53] = "5";
	keys[54] = "6";
	keys[55] = "7";
	keys[56] = "8";
	keys[57] = "9";
	keys[91] = "Win";
	keys[96] = "0";
	keys[97] = "1";
	keys[98] = "2";
	keys[99] = "3";
	keys[100] = "4";
	keys[101] = "5";
	keys[102] = "6";
	keys[103] = "7";
	keys[104] = "8";
	keys[105] = "9";
	keys[106] = "*";
	keys[107] = "+";
	keys[109] = "num -";
	keys[110] = "num ,";
	keys[111] = "num /";
	keys[112] = "F1";
	keys[113] = "F2";
	keys[114] = "F3";
	keys[115] = "F4";
	keys[116] = "F5";
	keys[117] = "F6";
	keys[118] = "F7";
	keys[119] = "F8";
	keys[120] = "F9";
	keys[121] = "F10";
	keys[122] = "F11";
	keys[123] = "F12";
	keys[144] = "Num";
	keys[145] = "Scr";
	keys[186] = ";";
	keys[188] = ",";
	keys[189] = "-";
	keys[190] = ".";
	keys[219] = "[";
	keys[221] = "]";
	keys[222] = "\'";

	return keys;
}