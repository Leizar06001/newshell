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

char	**split_cmds(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '"')
			continue ;
		j = -1;
		while (args[i][++j])
		{
			if (is_split_char(args[i][j]))
			{
				if (args[i][j + 1] == args[i][j])
					j++;
				tmp = add_str_arr_pos(args, i + 1, ft_strdup(args[i] + j));
				free(args);
				args = tmp;
				tmp = add_str_arr_pos(args, i + 2, ft_strdup(args[i] + j + 1));
				free(args);
				args = tmp;
				args[i][j] = '\0';
				args[i + 1][1] = '\0';
				i++;
				break ;
			}
		}
	}
	return (args);
}

char	**split_spaces(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (args[++i])
	{
		j = -1;
		if (args[i][0] == '\'' || args[i][0] == '"')
			continue ;
		while (args[i][++j])
		{
			if (is_spaces(args[i][j]))
			{
				// printf("SPLIT SPACE: %s\n", args[i]);
				tmp = add_str_arr_pos(args, i + 1, ft_strdup(args[i] + j + 1));
				free(args);
				args = tmp;
				args[i][j] = '\0';
				break ;
			}
		}
	}
	return (args);
}

char	**trim_all_str(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (is_only_spaces(args[i]) || is_only_quotes(args[i]))
		{
			args = rm_arr_line(args, i);
			i--;
		}
		else
		{
			ft_reduce_multiple_spaces(args[i]);
			tmp = ft_trim(args[i]);
			free(args[i]);
			args[i] = tmp;
		}
	}
	return (args);
}

char	**remove_quotes(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '"' || args[i][0] == '\'')
		{
			tmp = ft_strldup(args[i] + 1, ft_strlen(args[i]) - 2);
			free(args[i]);
			args[i] = tmp;
		}
	}
	return (args);
}

char	**parse(char *cmd_line)
{
	char	**args;

	(void)cmd_line;
	//char *str = "echo 'in\"si\"de' sp   aa cee d''ou\"\"ble 'this $USER''is'\"a $USER\" test \"|\" new | ls|grep < file $USE[] a > $USEER";
	char	*str = cmd_line;

	printf("\n\nTest: %s\n", str);
	if (check_quotes_closing(str) < 0)
		return (NULL);
	//printf("Check quotes ok\n");
	args = malloc(sizeof(char *) * 1);
	args[0] = NULL;

	args = analyse_quotes(args, str);
	args = replace_vars(args);

	// printf("\n");
	// prt_arg(args);

	args = split_cmds(args);

	// printf("\nSplitted:");
	// prt_arg(args);

	args = trim_all_str(args);

	// printf("\nTrimed:");
	// prt_arg(args);


	args = split_spaces(args);
	args = remove_quotes(args);

	// printf("\nLAST:");
	// prt_arg(args);

	// printf("\n");
	// int	i = -1;
	// while (args[++i])
	// {
	// 	int	j = -1;
	// 	while (args[i][++j])
	// 		printf("%c", args[i][j]);
	// 	printf(" ");
	// }
	// printf("\n");
	return (args);
}

/*

verif si les quotes se ferment bien

Séparer tout ce qui est entre cotes
Convertir les $VARS
Séparer les args

rejoindre les cotes contigues en 1 case
gerer les >> <<


*/
