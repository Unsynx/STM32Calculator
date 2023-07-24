# include <iostream>
#include <sstream>
#include <cmath>
#include "InputManager.h"

using namespace std;

void InputManager::printCommands() {
    cout << "0-9\tInput a number." << endl;
    cout << ".\tDecimal Point." << endl;
    cout << ADDITION_COMMAND << "\tAddition." << endl;
    cout << SUBTRACTION_COMMAND << "\tSubtraction." << endl;
    cout << MULTIPLICATION_COMMAND << "\tMultiplication." << endl;
    cout << DIVISION_COMMAND << "\tDivision." << endl;
    cout << EQUALS_COMMAND << "\tEvaluate Answer." << endl;
    cout << EXIT_COMMAND << "\tExit." << endl << endl;
}

bool InputManager::isCommand(char input) {
    if (input == '.') {                             // Checks if input is a decimal point
        return false;
    }
    if ((int)input >= 48 && (int)input <= 57) {     // Checks if input is a number
        return false;
    }
    return true;
}

void InputManager::saveNumber() {
    // Convert saved chars to an int
    stringstream ss;
    for (int i = 0; i <= inputBufferIndex; i++) {
        ss << inputBuffer[i];
    }

    float num;
    ss >> num;
    numbers[commandCount] = num;
    commandCount++;

    inputBufferIndex = 0;       
}

void InputManager::saveInput(char input) {
    // Adds input to buffer.
    inputBuffer[inputBufferIndex] = input;
    inputBufferIndex++;

    if (isCommand(input)) {                     // If input is a command
        commandList[commandCount] = input;      // Save command to commmand list
        saveNumber();                           // And save numbers to number list, reset input buffer
    }
}

void InputManager::shiftNumbers(float startValue, int start, int end) {
    for (int i = start; i < end; i++) {
        numbers[start + i] = numbers[start + i + 1];
    }
    numbers[start] = startValue;
};

void InputManager::shiftCommands(char startValue, int start, int end) {
    for (int i = start; i < end; i++) {
        commandList[start + i] = commandList[start + i + 1];
    }
    commandList[start] = startValue;
};

void InputManager::printArray(int start, int end) {
    for (int i = start; i < end; i++) {
        cout << i << "\t" << flush;
    }
    cout << endl;
    for (int i = start; i < end; i++) {
        cout << numbers[i] << " " << commandList[i] << "\t" << flush;
    }
    cout << endl;
}

float InputManager::operands(int i, char command) {
    switch (command)
    {
    case (MULTIPLICATION_COMMAND):
        return numbers[i] * numbers[i + 1];
    case (DIVISION_COMMAND):
        return numbers[i] / numbers[i + 1];
    case (ADDITION_COMMAND):
        return numbers[i] + numbers[i + 1];
    case (SUBTRACTION_COMMAND):
        return numbers[i] - numbers[i + 1];
    case (POWER_COMMAND):
        return pow(numbers[i], numbers[i + 1]);
    }
}


float InputManager::solveEquation(int start, int end, bool initialCall) {
    if (initialCall) {
        end = commandCount;
        cout << endl;
        printArray(start, end);
    }
    else {
        // Pass in smaller array without numbers
        cout << endl << endl;
        printArray(start, end);
        cout << "Parenthesis pair from " << start - 1 << " to " << end - 1 << endl;
    }


    int groupStart = -1;
    int startParenthesisCount = 0;
    for (int i = start; i < end; i++) {
        if (commandList[i] == PARENTHESIS_START) {
            if (groupStart == -1) {
                groupStart = i;
            }
            startParenthesisCount++;
            cout << "Parenthesis start found at i: " << i << endl;
        }
        if (commandList[i] == PARENTHESIS_END) {
            cout << "Parenthesis end found at i: " << i << endl;
            startParenthesisCount--;
            if (startParenthesisCount == 0) {
                // Plus one
                solveEquation(groupStart + 1, i + 1, false);
            }
        }
    }


    // Debug
    cout << "End" << endl << endl;
    commandCount = 0;
    inputBufferIndex = 0;
    return 0;

    cout << endl << "Calculations for " << start - 1 << " to " << end - 1 << endl;

    // Power
    for (int i = start; i < end; i++) {
        if (commandList[i] == POWER_COMMAND) {
            shiftNumbers(operands(i, commandList[i]), i, end);
            shiftCommands(commandList[i + 1], i, end);
            end--;
            i--;

            printArray(start, end);
        }
    }

    // Multiplication and division
    for (int i = start; i < end; i++) {
        if (commandList[i] == MULTIPLICATION_COMMAND || commandList[i] == DIVISION_COMMAND) {
            shiftNumbers(operands(i, commandList[i]), i, end);
            shiftCommands(commandList[i + 1], i, end);
            end--;
            i--;

            printArray(start, end);
        }
    }

    // Addition and subtraction
    for (int i = start; i < end; i++) {
        if (commandList[i] == ADDITION_COMMAND || commandList[i] == SUBTRACTION_COMMAND) {
            shiftNumbers(operands(i, commandList[i]), i, end);
            shiftCommands(commandList[i + 1], i, end);
            end--;
            i--;

            printArray(start, end);
        }
    }

    // Resets InputManager for next series of inputs
    commandCount = 0;
    inputBufferIndex = 0;

    answer = numbers[start];
    cout << "Answer: " << answer << endl;
    return answer;
}

char InputManager::getInput() {
    InputManager::printCommands();

    cout << "Enter a command: " << flush;

    // With STM32, this will manage the button matrix
    char input;
    cin >> input;

    return input;
}