#ifndef ASCII_H
#define ASCII_H


#include "simData.h"

extern std::string hex[128];

extern std::string binary[128];

std::string hex_to_binary(std::string hex_);

unsigned binary_to_decimal(std::string binary_);

#endif