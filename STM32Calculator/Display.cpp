#include <iostream>
#include "Display.h"

using namespace std;

string const Display::BORDER = "+----------------+";

void Display::clearDisplay() {
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
};

// When used with the STM32, this should interact with the display instead of printing to the console.
void Display::updateDisplay() {
	cout << BORDER << endl;
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		cout << '|' << flush;
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			cout << screen[i][j] << flush;
		}
		cout << '|' << endl;
	}
	cout << BORDER << endl;
};

void Display::setChar(char letter, int row, int column) {
	if (row > SCREEN_HEIGHT - 1 || row < 0) {
		throw invalid_argument("Outside display range");
	}
	if (column > SCREEN_WIDTH - 1 || column < 0) {
		throw invalid_argument("Outside display range");
	}

	screen[row][column] = letter;
};

void Display::writeLine(string line, int row, int align) {
	int len = line.length();
	if (align == ALIGN_LEFT) {
		for (int i = 0; i < len; i++) {
			setChar(line[i], row, i);
		}
	}
	else if (align == ALIGN_RIGHT) {
		for (int i = 1; i <= len; i++) {	// i starts at 1 to avoid null terminator
			setChar(line[len - i], row, SCREEN_WIDTH - i);
		}
	}
};

void Display::writeCursor(char letter) {
	setChar(letter, 0, cursorX);
	cursorX++;
};