#include "parseHelper.h"

short parseToShort (char byte_1, char byte_0) {
	return (((short) byte_1 ) << 8) | byte_0;
}