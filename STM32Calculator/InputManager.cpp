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
    cout << EQUALS_COMMAND << "\tEvaluate Answer." << endl;
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

//
void InputManager::mathLoop(vector<string> &queue, vector<char> operands, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        bool matchingCommand = false;

        for (int j = 0; j < operands.size(); j++) {
            if (queue[i][0] == operands[j]) {
                matchingCommand = true;
            }
        }

        if (matchingCommand) {
            float a = stof(queue[i - 1]);
            float b = stof(queue[i + 1]);
            float value = this->operands(queue[i][0], a, b);

            // squashes down the equation to a single element
            queue[i - 1] = to_string(value);
            queue.erase(next(queue.begin(), i + 1));
            queue.erase(next(queue.begin(),  i));
        }
    }
}

// Runs mathLoop for each set of operands.
void InputManager::math(vector<string> &queue, int startIndex, int endIndex) {
    vector<char> operands;

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

// Solves the equation saved in the input buffer
float InputManager::solveEquation() {
    vector<string> queue;

    // Convert char array to string array with grouped numbers
    stringstream ss;
    bool clearSS = true;
    for (int i = 0; i < inputBufferIndex; i++) {
        char c = inputBuffer[i];
        if (isCommand(c)) {
            string s;
            if (!clearSS) {

                ss >> s;
                queue.emplace_back(s);
                ss.str("");
                ss.clear();
            }

            string s2;
            ss << c;
            ss >> s2;
            queue.emplace_back(s2);
            ss.str("");
            ss.clear();

            clearSS = true;
        }
        else {
            ss << c;
            clearSS = false;
        }
    }

    math(queue, 0, queue.size()-2);

    inputBufferIndex = 0;
    float output = stof(queue[0]);
    return output;
}