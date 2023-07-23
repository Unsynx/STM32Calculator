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

bool InputManager::isNumber(char input) {
    if (input != '.' && (int)input <= 48 && (int)input >= 57) {   // Checks if input is a number or a decimal point
        cout << "Command" << endl;
        return true;
    }
    return false;
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

    if (!isNumber(input)) {                     // If input is a command
        commandList[commandCount] = input;      // Save command to commmand list
        saveNumber();                           // And save numbers to number list, reset input buffer
    }
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

    return input;
}