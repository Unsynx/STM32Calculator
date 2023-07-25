# include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include "InputManager.h"

using namespace std;

// For console. Replace with logic for key matrix
char InputManager::getInput() {
    // Console command list
    cout << "0-9\tInput a number." << endl;
    cout << ".\tDecimal Point." << endl;
    cout << ADDITION_COMMAND << "\tAddition." << endl;
    cout << SUBTRACTION_COMMAND << "\tSubtraction." << endl;
    cout << MULTIPLICATION_COMMAND << "\tMultiplication." << endl;
    cout << DIVISION_COMMAND << "\tDivision." << endl;
    cout << PARENTHESIS_START << ", " << PARENTHESIS_END << "\tParenthesis." << endl;
    cout << EQUALS_COMMAND << "\tEvaluate Answer." << endl;
    cout << CLEAR_COMMAND << "\tClear." << endl << endl;
    cout << EXIT_COMMAND << "\tExit." << endl << endl;

    // Input
    // Key matrix will likely use a while loop. Or interupts?
    cout << "Enter a command: " << flush;
    char input;
    cin >> input;

    return input;
}

// Adds input to buffer.
void InputManager::saveInput(char input) {
    inputBuffer[inputBufferIndex] = input;
    inputBufferIndex++;
}

// Apply an operand on two floats
float InputManager::operands(char command, float a, float b) {
    switch (command)
    {
    case (MULTIPLICATION_COMMAND):
        return a * b;
    case (DIVISION_COMMAND):
        return a / b;
    case (ADDITION_COMMAND):
        return a + b;
    case (SUBTRACTION_COMMAND):
        return a - b;
    case (POWER_COMMAND):
        return pow(a, b);
    default:
        return 0.0;
    }
}

// Returns whether or not charector is a command
bool InputManager::isCommand(char input) {
    if (input == '.') {                             // Checks if input is a decimal point
        return false;
    }
    if ((int)input >= 48 && (int)input <= 57) {     // Checks if input is a number
        return false;
    }
    return true;
}

// Do math and squish function
void InputManager::mathLoop(vector<string> &queue, vector<char> operands, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {  // i feel like this is the problem
        bool matchingCommand = false;

        // Catch weird error
        if (i == queue.size()) {
            return;
        }

        for (int j = 0; j < operands.size(); j++) {
            if (queue[i][0] == operands[j]) {
                matchingCommand = true;
            }
        }

        if (matchingCommand) {
            float a = stof(queue[i - 1]);
            float b = stof(queue[i + 1]);
            float value = this->operands(queue[i][0], a, b);

            int sizeBefore = queue.size();

            // squashes down the equation to a single element
            queue[i - 1] = to_string(value);
            queue.erase(next(queue.begin(), i + 1));
            queue.erase(next(queue.begin(),  i));
            queue.shrink_to_fit();

            endIndex -= (sizeBefore - queue.size());
            i = startIndex;
        }
    }
}

// Runs mathLoop for each set of operands.
void InputManager::math(vector<string> &queue, int startIndex, int endIndex) {
    vector<char> operands;

    if (queue[startIndex][0] == PARENTHESIS_START) {
        queue.erase(next(queue.begin(), endIndex));
        queue.erase(next(queue.begin(), startIndex));
        queue.shrink_to_fit();
        endIndex -= 2;
    }

    operands.emplace_back(POWER_COMMAND);
    mathLoop(queue, operands, startIndex, endIndex);

    operands.clear();
    operands.emplace_back(MULTIPLICATION_COMMAND);
    operands.emplace_back(DIVISION_COMMAND);
    mathLoop(queue, operands, startIndex, endIndex);

    operands.clear();
    operands.emplace_back(ADDITION_COMMAND);
    operands.emplace_back(SUBTRACTION_COMMAND);
    mathLoop(queue, operands, startIndex, endIndex);
}


void InputManager::addToQueue(vector<string>& queue, stringstream& ss) {
    string s;
    ss >> s;
    queue.emplace_back(s);
    ss.str("");
    ss.clear();
}

int InputManager::parseInput() {
    queue.clear();

    // Convert char array to string array with grouped numbers
    stringstream ss;
    bool clearSS = true;
    for (int i = 0; i < inputBufferIndex; i++) {
        char c = inputBuffer[i];
        if (isCommand(c)) {
            if (!clearSS) {
                addToQueue(queue, ss);

                // When no operator is place between a parenthesis and a number, it default to multiplying them.
                if (c == PARENTHESIS_START) {
                    ss << MULTIPLICATION_COMMAND;
                    addToQueue(queue, ss);
                }
            }
            else {
                return SYNTAX_ERROR;
            }

            ss << c;
            addToQueue(queue, ss);
            clearSS = true;

            // When no operator follows an ending parenthesis, default to multiplying them.
            if (isCommand(c) && c == PARENTHESIS_END && !isCommand(inputBuffer[i + 1])) {
                ss << MULTIPLICATION_COMMAND;
                addToQueue(queue, ss);
            }
        }
        else {
            ss << c;
            clearSS = false;
        }
    }
    return 0;
}

// Solves the equation saved in the input buffer
float InputManager::solveEquation() {
    int end = queue.size();
    int parenthesisStart = 0;
    for (int i = 0; i < end; i++) {
        if (queue[i][0] == PARENTHESIS_START) {
            parenthesisStart = i;
        }
        if (queue[i][0] == PARENTHESIS_END) {
            math(queue, parenthesisStart, i);
            i = 0;
            parenthesisStart = 0;
            end = queue.size();
        }
    }

    math(queue, 0, queue.size() - 1);

    inputBufferIndex = 0;
    float output = stof(queue[0]);
    return output;
}