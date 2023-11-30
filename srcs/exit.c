#include "../includes/minishell.h"

void	exit_minishell(void)
{
	printf("\nExit\n");
	// FREE ALL MALLOCS
	int	i = -1;
	while (g_data.copy_env[++i])
		free(g_data.copy_env[i]);
	free(g_data.copy_env);
	free(g_data.prompt);
	exit(0);
}
