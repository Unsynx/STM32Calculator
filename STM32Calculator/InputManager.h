#pragma once

#include <iostream>

using namespace std;

class InputManager {
private:
	char inputBuffer[100] = {};		//  List of all the numbers you input
	int inputBufferIndex = 0;		//  How many places are filled

	float numbers[100] = {};		//  Inputed numbers turned from chars to ints
	char commandList[100] = {};		//  List of commands in the order applied
	int commandCount = 0;			//  How many numbers are filled

	float answer = 0;

public:
	static char const ADDITION_COMMAND = '+';
	static char const SUBTRACTION_COMMAND = '-';
	static char const MULTIPLICATION_COMMAND = '*';
	static char const DIVISION_COMMAND = '/';
	static char const POWER_COMMAND = '^';
	static char const EQUALS_COMMAND = '=';
	static char const PARENTHESIS_START = '(';
	static char const PARENTHESIS_END = ')';

	static char const EXIT_COMMAND = 'e';  // for testing only

private:
	void printCommands();
	void saveNumber();
	bool isCommand(char input);
	void shiftNumbers(float startValue, int start, int end);
	void shiftCommands(char startValue, int start, int end);
	float operands(int i, char command);
	void printArray(int start = 0, int end = 5); // for debug

public:
	InputManager() {};
	float solveEquation(int start = 0, int end = 0, bool initialCall = true);
	char getInput();	// With STM32, this will manage the button matrix
	void saveInput(char input);
	float getAnswer() { return answer; }
};
