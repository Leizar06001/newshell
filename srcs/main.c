#include "../includes/minishell.h"

t_data g_data;

void	prt_args(t_data *datas)
{
	// int	i;

	// i = 0;
	// printf("args: ");
	// while (args[i])
	// {
	// 	printf("%d[%s] ", i, args[i]);

	// 	i++;
	// }
	// printf("\n\n");
	int	i = -1;
	printf("\n\n*** New array ***\n");
	while (datas->args_arr[++i])
	{
		printf("\nLine %d\n >> ", i);
		int j = -1;
		while (datas->args_arr[i][++j])
			printf("%s ", datas->args_arr[i][j]);
	}
	printf("\n");
}

int	cmd_launcher(t_data *datas)
{
	int	i;
	int		err;

	i = -1;
	while (datas->args_arr[++i])
	{
		if (datas->args_arr[i][0][0] != '|')
		{
			printf("\n>>> Command output:\n");
			err = my_execve(datas->args_arr[i]);	// system program
			if (err != 0)
				err = look_for_builtin(datas->args_arr[i]);	// builtins
		}
	}
	return (err);
}

void	main_command_loop(void)
{
	int		err;

	(void)err;
	while (!g_data.exit)
	{
		err = 0;
		g_data.cmd_line = readline(g_data.prompt);

		if (g_data.cmd_line == NULL)
			break ;
		if (g_data.cmd_line[0])
		{
			add_history(g_data.cmd_line);

			parse(g_data.cmd_line, &g_data);
			prt_args(&g_data);

			// err = my_execve(args);	// system program
			// if (err != 0)
			// 	err = look_for_builtin(args);	// builtins
			err = cmd_launcher(&g_data);
			clear_data_args_arr(&g_data);
		}
		free(g_data.cmd_line);
	}
}

//char *args[] = {"echo", "La maison", NULL};

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	// char	**args;

	init_vars(env);
	//parse("test", &g_data);


	main_command_loop();


	exit_minishell();



	// exit 42 ? (y)19
	return (0);
}
