#pragma once
#include "iprogress.h"
#include <string>

class ConsolePrinter : public IProgress {
private:
	bool m_showText;
	const std::string YELLOW;
	const std::string RESET;
	const int BAR_WIDTH;

public:
	ConsolePrinter();
	void update(double fraction) override;
};
