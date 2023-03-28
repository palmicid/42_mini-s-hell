#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	for (int i = 0; env[i]; i++)
	{
		printf("%s\n", env[i]);
	}
	return 0;
}