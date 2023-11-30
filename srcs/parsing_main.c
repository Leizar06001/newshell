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

char	**join_quotes(char **args, int start, int end)
{
	int	len;
	int	i;

	i = start;
	while (++i <= end)
		len += ft_strlen(args[i]);
	printf("Total len: %d\n", len);
	return (args);
}

char	**check_quotes_to_join(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '"')
		{
			j = i;
			while (args[j + 1])
			{
				if (args[j + 1][0] == '\'' || args[j + 1][0] == '"')
					j++;
				else
					break ;
			}
			printf("Found quotes from %d to %d\n", i, j);
			if (j > i)
			{
				join_quotes(args, i, j);
				i = j;
			}
		}
	}
	return (args);
}

char	**parse(char *cmd_line)
{
	char	**args;

	(void)cmd_line;
	char *str = "echo 'in\"si\"de' sp   aa cee d''ou\"\"ble 'this $USER''is'\"a $USER\" test \"|\" new | ls|grep < file $USE[] a > $USEER";
	//char	*str = cmd_line;

	printf("\n\nTest: %s\n", str);
	if (check_quotes_closing(str) < 0)
		return (NULL);
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

	printf("\nSpaces:");
	prt_arg(args);

	args = check_quotes_to_join(args);

	args = remove_quotes(args);
	// printf("\nLAST:");
	// prt_arg(args);
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
