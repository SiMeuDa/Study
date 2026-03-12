#include "mode.h"

int mode::run(void)
{
	uint64_t msg = 1234;
	uint64_t output;
	uint64_t key = 1234;

	output = cipher(msg, key);

	if(msg == decipher(output, key))
		return 1;
	else
		return -1;
}
