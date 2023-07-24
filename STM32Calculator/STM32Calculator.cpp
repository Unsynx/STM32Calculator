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

    bool clearDisplay = true;
    
    // Main loop
    do {
        //system("cls");                      // clears screen
        display.updateDisplay();            // Pushes all updates from display class to console

        // Clears display after 
        if (clearDisplay) {
            display.clearDisplay();
            clearDisplay = false;
        }

        input = inputManager.getInput();    // Waits until input is received
        inputManager.saveInput(input);      // Saves input to input buffer

        if (input == InputManager::EQUALS_COMMAND) {
            inputManager.solveEquation();

            stringstream ss;
            ss << "=" << inputManager.getAnswer();
            
            string ans;
            ss >> ans;

            display.writeLine(ans, 1, Display::ALIGN_RIGHT);
            clearDisplay = true;
            display.resetCursor();
        }
        else {
            display.writeCursor(input, true);
        }

    } while (input != InputManager::EXIT_COMMAND);
}
