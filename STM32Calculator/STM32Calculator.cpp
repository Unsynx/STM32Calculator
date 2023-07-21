// STM32Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "Display.h"
#include "InputManager.h"

using namespace std;

int main()
{
    Display display;
    InputManager inputManager;
    char input;

    // Intro screen
    display.writeLine("Hello. world!", 0, Display::ALIGN_LEFT);
    display.updateDisplay();
    input = inputManager.getInput();
    display.clearDisplay();
    display.writeCursor(input);     // May have to change this
    
    // Main loop
    do {
        system("cls");  // clears screen
        display.updateDisplay();

        input = inputManager.getInput();
        if (input == InputManager::EQUALS_COMMAND) {
            stringstream ss;
            ss << "=" << inputManager.getAnswer();
            string ans;
            ss >> ans;
            display.writeLine(ans, 1, Display::ALIGN_RIGHT);
        }
        else {
            display.writeCursor(input);
        }

    } while (input != InputManager::EXIT_COMMAND);
}
