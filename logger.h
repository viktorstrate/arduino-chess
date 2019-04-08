//
// Created by Viktor Hundahl Strate on 18/02/2019.
//

#pragma once

#ifdef DESKTOP
#include <iostream>
#else
#include <Arduino.h>
#endif

#ifdef DESKTOP
#define Print(message) std::cout << message
#else
#define Print(message) Serial.print(message)
#endif

#ifdef DESKTOP
#define Println(message) std::cout << message << std::endl
#else
#define Println(message) Serial.println(message)
#endif
