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
    for (int i = 0; i < end - start; i++) {
        numbers[start + i] = numbers[start + i + 1];
    }
    numbers[start] = startValue;
};

void InputManager::shiftNumbers2(int start, int end) {
    for (int i = 0; i < end - start; i++) {
        numbers[start + i] = numbers[start + i + 1];
    }
};

void InputManager::shiftCommands(char startValue, int start, int end) {
    for (int i = 0; i < end - start; i++) {
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

void InputManager::mathLoop(char* commands, int* start, int* end, int operCount) {
    const int rangeEnd = *end;
    for (int i = *start; i < *end; i++) {
        bool matchingCommand = false;

        for (int j = 0; j < operCount; j++) {
            if (commandList[i] == commands[j]) {
                matchingCommand = true;
            }
        }

        if (matchingCommand) {
            cout << endl << "command: " << commandList[i] << endl;  // Debug

            float value = operands(commandList[i], numbers[i], numbers[i+1]);
            cout << "computed value: " << value << endl;
            cout << "Before shift:" << endl;

            printArray(0, 10);
            cout << endl;
            shiftNumbers(value, *start, rangeEnd);
            shiftCommands(commandList[i + 1], *start, rangeEnd);

            (*end)--;
            i--;

            cout << "After shift:" << endl;
            printArray(0, 10);  // Debug
            cout << endl;
        }
    }
};

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
                int chunkLength = i - groupStart;
                float value = solveEquation(groupStart + 1, i + 1, false);

                /*  
                (5+2)*((14/7)+1)=
                ((14/7)+1)*(5+2)=
                */

                // todo: figure out how to change the selected area of the parenthesis after it has been shifted.

                cout << "Before format, chunkLength: " << chunkLength << endl;
                printArray();

                // Shift result over
                for (int j = 0; j < chunkLength; j++) {
                    shiftNumbers(value, groupStart, i + 1);
                    shiftCommands(commandList[groupStart + 1], groupStart, i + 1);
                }

                cout << "First step complete"<< endl;
                printArray();

                if (!initialCall) {
                    cout << "chunkLength: " << chunkLength << ", groupstart: " << groupStart << endl;
                }

                // Shift rest of equation over
                for (int j = 0; j <= chunkLength; j++) {
                    shiftNumbers2(groupStart + 1, sizeof(numbers) / sizeof(int));
                    shiftCommands(commandList[groupStart + 2], groupStart + 1, sizeof(commandList));
                }

                cout << "Second step. After format" << endl;
                printArray();

                i = start;
                groupStart = -1;
            }
        }
    }

    cout << endl << "Calculations for " << start - 1 << " to " << end - 1 << endl;
    printArray();

    int* pStart = &start;
    int* pEnd = &end;
    char commands[2] = {};

    commands[0] = POWER_COMMAND;
    mathLoop(commands, pStart, pEnd, 1);

    commands[0] = MULTIPLICATION_COMMAND;
    commands[1] = DIVISION_COMMAND;
    mathLoop(commands, pStart, pEnd);

    commands[0] = ADDITION_COMMAND;
    commands[1] = SUBTRACTION_COMMAND;
    mathLoop(commands, pStart, pEnd);


    // Resets InputManager for next series of inputs
    commandCount = 0;
    inputBufferIndex = 0;


    answer = numbers[start];
    cout << "RECURSE DONE" << endl << "Answer: " << answer << endl << endl;
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