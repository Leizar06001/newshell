#include "../includes/minishell.h"

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

int get_end_quote(char *str, int start, char type)
{
	while (str[++start])
	{
		if (str[start] == type)
			return (start);
	}
	return (-1);
}

int check_quotes_closing(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			i = get_end_quote(str, i, '"');
			if (i < 0)
			{
				printf("Error: Double quote missing\n");
				return (-1);
			}
		}
		else if (str[i] == '\'')
		{
			i = get_end_quote(str, i, '\'');
			if (i < 0)
			{
				printf("Error: Simple quote missing\n");
				return (-1);
			}
		}
	}
	return (0);
}

void	update_counters(int *i, int *endqu)
{
	*i = *endqu;
	*endqu = *endqu + 1;
}

char **analyse_quotes(char **args, char *str)
{
	int i;
	int endqu;

	i = -1;
	endqu = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			args = add_str_part_to_arr(args, str, endqu, i - 1);
			endqu = get_end_quote(str, i, '\"');
			args = add_str_part_to_arr(args, str, i, endqu);
		}
		else if (str[i] == '\'')
		{
			args = add_str_part_to_arr(args, str, endqu, i - 1);
			endqu = get_end_quote(str, i, '\'');
			args = add_str_part_to_arr(args, str, i, endqu);
		}
		if (str[i] == '\'' || str[i] == '\"')
			update_counters(&i, &endqu);
	}
	args = add_str_part_to_arr(args, str, endqu, i);
	return (args);
}
