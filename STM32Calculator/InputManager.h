#pragma once

#include <iostream>
#include <vector>

using namespace std;

class InputManager {
private:
	char inputBuffer[100] = {};		//  List of all the numbers you input
	int inputBufferIndex = 0;		//  How many places are filled

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
	float operands(char command, float a, float b);
	bool isCommand(char input);
	float mathLoop(vector<string> *ar, int startIndex, int endIndex);

public:
	float solveEquation();
	char getInput();
	void saveInput(char input);
	float getAnswer() { return answer; }
};
