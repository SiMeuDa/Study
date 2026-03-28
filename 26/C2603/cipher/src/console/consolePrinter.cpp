#include "consolePrinter.h"
#include <iostream>
#include <iomanip>

ConsolePrinter::ConsolePrinter() : m_showText(true), YELLOW("\033[38;5;214m"), RESET("\033[0m"), BAR_WIDTH(20) {}

void ConsolePrinter::update(double fraction) {

	int pos = static_cast<int>(BAR_WIDTH * fraction);

	std::cout << "\r" << YELLOW << "{";
	
	for (int i = 0; i < BAR_WIDTH; ++i)
	{
		if (i < pos) 
			std::cout << "#";
		else 
			std::cout << "=";	
	}

	std::string blinkText = m_showText ? " Loading..." : "           ";
	
	m_showText = !m_showText;
	
	std::cout << "} " << blinkText << " (" << std::fixed << std::setprecision(0) << (fraction * 100) << "%)" << RESET << std::flush;
    if (fraction >= 1.0) {
		std::cout << "\r" << YELLOW << "{" << std::string(BAR_WIDTH, '#') << "}  Complete! (100%)" << RESET << std::endl;												    
	}	
}
