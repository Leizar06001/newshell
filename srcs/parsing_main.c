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

int get_end_quote(char *str, int start, char type)
{
	//printf("End quote\n");
	while (str[++start])
	{
		//printf("%c", str[start]);
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

char **add_one_array_line(char **arr, int pos, char *str)
{
	int		i;
	int		len;
	char	**ret;

	// printf("ADD LINE\n");
	len = 0;
	while (arr[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	i = -1;
	if (pos > len)
		pos = len;
	while (++i < pos){
		ret[i] = arr[i];
		printf("copy line %d\n", i);
	}
	ret[i] = str;
	while (++i < len){
		ret[i] = arr[i - 1];
		printf("copy line %d\n", i);
	}
	ret[i] = NULL;
	printf("> New length: %d, NULL at %d\n", len + 2, i);
	free(arr);
	return (ret);
}

char **fill_box_dquote(char **args, char *str, int start, int end)
{
	char *extract;

	// printf("Len strdup: %d\n", end - start);
	extract = ft_strldup(str + start, end - start + 1);
	printf("Adding > %s <\n", extract);
	args = add_one_array_line(args, 9999999, extract);
	return (args);
}

char **analyse_quotes(char **args, char *str)
{
	int i;
	int nexti;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			// printf("Found quote at %d\n", i);
			// printf("%s\n", str + i);
			nexti = get_end_quote(str, i, '\"');
			// printf("> Next quote at %d\n", nexti);
			args = fill_box_dquote(args, str, i, nexti);
			i = nexti;
		}
	}
}



char	**parse(char *cmd_line)
{
	char	**args;
	char	**tmp;

	(void)cmd_line;
	char *str = "echo 'this''is'\"a\" test \"|\" | ls|grep < file a";

	printf("Test: %s\n", str);
	if (check_quotes_closing(str) < 0)
		return (-1);
	printf("Check quotes ok\n");
	args = malloc(sizeof(char *) * 1);
	args[0] = NULL;
	tmp = analyse_quotes(args, str);

	prt_arg(tmp);

	return (args);
}

/*

verif si les quotes se ferment bien

Séparer tout ce qui est entre cotes
Convertir les $VARS
Séparer les args


*/
