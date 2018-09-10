#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	while (1);
	while (*argv)
		printf("'%s'\n", *argv++);
	return (0);
}
