#pragma once

#include <iostream>

void errorMessage(char* error)
{
	std::cout << error << std::endl;
	exit(0);
}