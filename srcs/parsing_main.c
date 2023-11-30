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
	int	i;
	int	j;

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
				printf("\nArgs[%d] {%s} Found split char: %c\n", i, args[i], args[i][j]);
				args = add_str_arr_pos(args, i + 1, ft_strdup(args[i] + j));
				args = add_str_arr_pos(args, i + 2, ft_strdup(args[i] + j + 1));
				args[i][j] = '\0';
				args[i + 1][1] = '\0';
				printf("Modify to: {%s}\n", args[i]);
				printf("Add: {%s}\n", args[i + 1]);
				printf("And: {%s}\n", args[i + 2]);
				i++;
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
		tmp = ft_trim(args[i]);
		free(args[i]);
		args[i] = tmp;
	}
	return (args);
}

char	**parse(char *cmd_line)
{
	char	**args;

	(void)cmd_line;
	char *str = "echo 'in\"si\"de' 'this $USER''is'\"a $USER\" test \"|\" new | ls|grep << file $USER a > $USER";

	printf("\n\nTest: %s\n", str);
	if (check_quotes_closing(str) < 0)
		return (NULL);
	//printf("Check quotes ok\n");
	args = malloc(sizeof(char *) * 1);
	args[0] = NULL;
	args = analyse_quotes(args, str);
	args = replace_vars(args);

	printf("\n");
	prt_arg(args);

	args = split_cmds(args);

	printf("\n");
	prt_arg(args);

	args = trim_all_str(args);

	printf("\n");
	prt_arg(args);

	int i = -1;
	while (args[++i])
		free(args[i]);
	free(args);

	return (args);
}

/*

verif si les quotes se ferment bien

Séparer tout ce qui est entre cotes
Convertir les $VARS
Séparer les args


*/
