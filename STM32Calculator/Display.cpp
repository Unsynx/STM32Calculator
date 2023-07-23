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

// Sets a specific display cell to a char
void Display::setChar(char letter, int row, int column) {
	if (row > SCREEN_HEIGHT - 1 || row < 0) {
		throw invalid_argument("Outside display range");
	}
	if (column > SCREEN_WIDTH - 1 || column < 0) {
		throw invalid_argument("Outside display range");
	}

	screen[row][column] = letter;
};

// Write a string to a specific display row. With alignment.
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

void Display::shiftRow(int row, int direction) {
	if (direction == Display::LEFT) {
		for (int i = 0; i < Display::SCREEN_WIDTH; i++) {
			setChar(screen[row][i+1], row, i);
		}
	} else if (direction == Display::RIGHT) {
		// Not something I need
	}
}

// Writes to a specific row but moves 
void Display::writeCursor(char letter, bool shiftDisplayWhenFull) {
	if (cursorX == SCREEN_WIDTH && shiftDisplayWhenFull) {
		shiftRow(0, Display::LEFT);
		setChar(letter, 0, SCREEN_WIDTH - 1);
	}
	else {
		setChar(letter, 0, cursorX);
		cursorX++;
	}
};