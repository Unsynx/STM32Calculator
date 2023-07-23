# include <iostream>
#include <sstream>
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

void InputManager::printArray() {
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << commandList[i] << flush;
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
    }
}


float InputManager::solveEquation() {
    // Check for parenthesis
    // Make sure this can identify both nested and sequential occurences.

    // Multiplication and division
    printArray();
    for (int i = 0; i < commandCount; i++) {
        if (commandList[i] == MULTIPLICATION_COMMAND || commandList[i] == DIVISION_COMMAND) {
            shiftNumbers(operands(i, commandList[i]), i, commandCount);
            shiftCommands(commandList[i + 1], i, commandCount);
            commandCount--;
            i--;

            // Debug
            printArray();
            cout << "i: " << i << ", commandCount: " << commandCount << endl;
        }
    }

    // Addition and subtraction
    for (int i = 0; i < commandCount; i++) {
        if (commandList[i] == ADDITION_COMMAND || commandList[i] == SUBTRACTION_COMMAND) {
            shiftNumbers(operands(i, commandList[i]), i, commandCount);
            shiftCommands(commandList[i + 1], i, commandCount);
            commandCount--;
            i--;

            // Debug
            printArray();
            cout << "i: " << i << ", commandCount: " << commandCount << endl;
        }
    }

    answer = numbers[0];
    return answer;
}

char InputManager::getInput() {
    InputManager::printCommands();

    cout << "Enter a command: " << flush;

    // With STM32, this will manage the button matrix
    char input;
    cin >> input;
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');   // Only read first char https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input

    return input;
}