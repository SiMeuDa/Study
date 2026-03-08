#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "feistel.h"

class DES : private feistel{
private:
protected:
	DES(std::string, uint64_t);
};
