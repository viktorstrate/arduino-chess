//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#pragma once

#ifdef DESKTOP
#include <iostream>
#else
#include <arduino.h>
#endif

#ifdef DESKTOP
#define print(message) std::cout << message
#else
#define print(message) Serial.print(message)
#endif

#ifdef DESKTOP
#define println(message) std::cout << message << std::endl
#else
#define println(message) Serial.println(message)
#endif
