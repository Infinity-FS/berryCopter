#include "parseHelper.h"

short parseToShort (char byte_0, char byte_1) {
	return (((short) byte_1 ) << 8) | byte_0;
}