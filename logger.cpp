//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#ifdef DESKTOP
#include <iostream>
#else
#include <arduino.h>
#endif

#include "logger.h"

void print(const char* message)
{
#ifdef DESKTOP
    std::cout << message;
#else
    Serial.print(message);
#endif
}

void println(const char* message)
{
#ifdef DESKTOP
    std::cout << message << std::endl;
#else
    Serial.println(message);
#endif
}