// STM32Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Display.h"

using namespace std;

int main()
{
    Display display;
    display.writeLine("Hello. world!", 0, Display::ALIGN_LEFT);
    display.updateDisplay();
}
