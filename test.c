#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[], char *env[])
{
	printf("%s\n", getenv("PATH"));
	return 0;
}
