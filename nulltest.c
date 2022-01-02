/*
* This test case tries to access the address 0x0 which should be throw
* a trap error in the new implementation
* 
* This test case throws a trap error as expected
*/

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
	int* a = 0x0;
	int b = *a;
	b += 4000;
	exit();
}
