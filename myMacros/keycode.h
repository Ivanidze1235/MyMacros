#pragma once
unsigned char Keycode(){
	BOOL key_found = false;
	unsigned char key;
	while (!key_found) {
		// iterates through all possible key codes
		for (int keyCode = 0; keyCode < 256; ++keyCode) {

			if (GetAsyncKeyState(keyCode) & 0x8000) {
				key = static_cast<unsigned char>(keyCode);
				key_found = true;
				break;
			}
		}
		Sleep(0.1);
	}

	return key;
}