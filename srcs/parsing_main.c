#include "../includes/minishell.h"

void	prt_arg(char **args)
{
	int	i;

	i = 0;
	printf("args: ");
	while (args[i])
	{
		printf("%d[%s] ", i, args[i]);
		i++;
	}
	printf("\n\n");
}

char	**join_double_redirs(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i + 1])
	{
		if ((args[i][0] == '>' || args[i][0] == '<') &&
			args[i][0] == args[i + 1][0])
		{
			tmp = malloc(sizeof(char) * 3);
			tmp[0] = args[i][0];
			tmp[1] = args[i][0];
			tmp[2] = '\0';
			free(args[i]);
			rm_arr_line(args, i + 1);
			args[i] = tmp;
		}
	}
	return (args);
}

char	**parse(char *cmd_line, t_data *datas)
{
	char	**args;

	(void)cmd_line;
	char *str = "echo 'in\"si\"de' sp   aa cee d''ou\"\"ble 'this \"$USER\"''is'\"a '$USER'\" test \"|\" new | ls|grep << file $USE[] a > $USEER";
	//char *str = "echo << file coucou";
	//char *str = "e";
	//char	*str = cmd_line;

	printf("\n\nTest: %s\n", str);
	if (check_quotes_closing(str) < 0)
		return (NULL);
	args = malloc(sizeof(char *) * 1);
	args[0] = NULL;
	args = analyse_quotes(args, str);
	args = replace_vars(args);
	args = split_cmds(args);
	args = trim_all_str(args);
	args = split_spaces(args);
	args = join_double_redirs(args);
	args = check_quotes_to_join(args);
	create_output(args, datas);

	//args = remove_quotes(args);
	printf("\nLAST:");
	prt_arg(args);
	// printf("\n");
	return (args);
}

