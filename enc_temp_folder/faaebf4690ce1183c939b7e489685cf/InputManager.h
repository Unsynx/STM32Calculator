#pragma once

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class InputManager {
private:
	char inputBuffer[100] = {};		//  List of all the numbers you input
	int inputBufferIndex = 0;		//  How many places are filled

	vector<string> queue;

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

	static char const CLEAR_COMMAND = 'c';  

	static char const EXIT_COMMAND = 'e';  // for testing only

	static int const GENERIC_ERROR = 0;

private:
	void addToQueue(vector<string>& queue, stringstream& ss);
	float operands(char command, float a, float b);
	bool isCommand(char input);
	void mathLoop(vector<string> &queue, vector<char> operands, int startIndex, int endIndex);
	void math(vector<string> &queue, int startIndex, int endIndex);
public:
	int parseInput();
	void clearInputBuffer() { inputBufferIndex = 0; };
	float solveEquation();
	char getInput();
	void saveInput(char input);
	float getAnswer() { return answer; }
};
