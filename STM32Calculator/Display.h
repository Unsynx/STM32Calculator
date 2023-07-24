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
	static int const RIGHT = 1;
	static int const LEFT = -1;

public:
	Display() { clearDisplay(); };
	void clearDisplay();
	void updateDisplay();
	void shiftRow(int row, int direction);
	void writeLine(string line, int row, int align);
	void writeCursor(char letter, bool shiftDisplayWhenFull);
	void resetCursor() { cursorX = 0; };
	void setChar(char letter, int row, int column);
};