#include "../includes/minishell.h"

int	is_alpha_num(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_split_char(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_spaces(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
