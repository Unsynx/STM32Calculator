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

void InputManager::solveEquation() {
    float runningValue = numbers[0];

    for (int i = 0; i < commandCount - 1; i++) {
        if (commandList[i] == SUBTRACTION_COMMAND) {
            runningValue -= numbers[i + 1];
        } else if (commandList[i] == ADDITION_COMMAND) {
            runningValue += numbers[i + 1];
        }
    }

    answer = runningValue;
}

char InputManager::getInput() {
    InputManager::printCommands();

    cout << "Enter a command: " << flush;

    // With STM32, this will manage the button matrix
    char input;
    cin >> input;
    // Only read first char https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');   
    cout << endl;

    // Adds input to buffer
    inputBuffer[inputBufferIndex] = input;
    inputBufferIndex++;

    // Adds command and number to their respective lists
    switch (input) {
    case (ADDITION_COMMAND):
        commandList[commandCount] = ADDITION_COMMAND;
        saveNumber();
        break;

    case (SUBTRACTION_COMMAND):
        commandList[commandCount] = SUBTRACTION_COMMAND;
        saveNumber();
        break;

    case (MULTIPLICATION_COMMAND):
        commandList[commandCount] = MULTIPLICATION_COMMAND;
        saveNumber();
        break;

    case (DIVISION_COMMAND):
        commandList[commandCount] = DIVISION_COMMAND;
        saveNumber();
        break;

    case (EQUALS_COMMAND):      // Solves equation and resets input buffers.
        saveNumber();
        solveEquation();
        commandCount = 0;
        break;

    default:
        break;
    }

    return input;
}