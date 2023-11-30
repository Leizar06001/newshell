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

void fill_box_dquote(char *str, int start, int end)
{

}

char **analyse_quotes(char *str)
{
	int i;
	int nexti;

	i = -1;
	while (str[++i])
	{
		if (str[i] == "\"")
		{
			//nexti = get_end_quote()
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
	tmp = analyse_quotes(str);

	//prt_arg(tmp);

	return (args);
}

/*

verif si les quotes se ferment bien

Séparer tout ce qui est entre cotes
Convertir les $VARS
Séparer les args


*/
