#include "minishell.h"

int	main(int ac, char **av)
{
	char	*strcmd;
	t_cmd	*fin = NULL;

	if (ac > 1)
	{
		strcmd = ft_strdup(av[1]);
		fin = str_split(strcmd, fin);

		free(strcmd);
	}
	printf("====== END-TEST ======\n");
	return (0);
}