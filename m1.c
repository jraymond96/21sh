#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	dprintf(2, "ERROR %s", argv[2]);
	sleep(atoi(argv[1]));
	return (0);
}
