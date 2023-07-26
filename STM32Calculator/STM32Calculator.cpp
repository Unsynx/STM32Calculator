// STM32Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // Console
#include <windows.h>    // Console 
#include <sstream>
#include <cmath>
#include "Display.h"
#include "InputManager.h"

using namespace std;

int main()
{
    Display display;
    InputManager inputManager;

    // Intro screen
    display.writeLine("Hello. world!", 0, Display::ALIGN_LEFT);

    bool clearDisplay = true;
    char input;
    
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
            // Error handling
            switch (inputManager.parseInput())
            {  
            case (InputManager::SYNTAX_ERROR):
                display.clearDisplay();
                display.writeLine("ERROR", 0, Display::ALIGN_LEFT);
                display.writeLine("Syntax Error", 1, Display::ALIGN_LEFT);
                inputManager.clearInputBuffer();
                clearDisplay = true;
                break;

            default:
                // Calculate answer and display it
                float answer = inputManager.solveEquation();

                stringstream ss;
                ss << "=" << answer;

                string answerString;
                ss >> answerString;

                display.writeLine(answerString, 1, Display::ALIGN_RIGHT);
                clearDisplay = true;
                display.resetCursor();
                break;
            }
        }
        else if (input == InputManager::CLEAR_COMMAND) {
            display.clearDisplay();
            inputManager.clearInputBuffer();

        } else {
            display.writeCursor(input, true);
        }

    } while (input != InputManager::EXIT_COMMAND);
}



/*
class Equation {
public:
    string equation;
    float answer;
public:
    Equation(string equation, float answer) : equation(equation), answer(answer) {};
    bool pass(float value) { return fabs(answer - value) < 0.001f; }
};


// Equation tests
int main() {
    Equation equations[] = {
        Equation("1+1=", 2),
        Equation("7-5+1=", 3),
        Equation("12*2/3=", 8),
        Equation("4-5*2=", -6),
        Equation("1.2-0.9=", 0.3),
        Equation("5.2*7=", 36.4),
        Equation("2^5=", 32),
        Equation("5*(1+4)=", 25),
        Equation("5*((5-1)/5)=", 4),
        Equation("1+(6-2)+(9+2)=", 16),
        Equation("(6+1)*4=", 28),
        Equation("(5+7)*((16-11)-(2^2))=", 12),
        Equation("10^(5-2)*(0.9)=", 900),
    };

    InputManager inputManager;

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < sizeof(equations) / sizeof(Equation); i++) {
        // Input equations into InputManager
        for (int j = 0; j < equations[i].equation.length(); j++) {
            inputManager.saveInput(equations[i].equation[j]);
        }

        if (inputManager.parseInput() != 0) {
            inputManager.clearInputBuffer();
            continue;
        }
        
        float answer = inputManager.solveEquation();
        bool pass = equations[i].pass(answer);

        // Set text color
        if (pass) {
            SetConsoleTextAttribute(hConsole, 15);
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
        }

        // Results
        cout << i << "\t" << (pass ? "PASS" : "FAIL") << "\t\"" 
            << equations[i].equation << equations[i].answer << "\" computed as: " << answer << endl;
    }

    SetConsoleTextAttribute(hConsole, 15);
}

*/