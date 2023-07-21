#pragma once

using namespace std;

class Display {
private:
	static int const SCREEN_HEIGHT = 2;
	static int const SCREEN_WIDTH = 16;
	static string const BORDER;

	char screen[2][16] = {};
	int cursorX = 0;

public:
	static int const ALIGN_RIGHT = 1;
	static int const ALIGN_LEFT = -1;

public:
	Display() { clearDisplay(); };
	void clearDisplay();
	void updateDisplay();
	void writeLine(string line, int row, int align);
	void writeCursor(char letter);
	void setChar(char letter, int row, int column);
};