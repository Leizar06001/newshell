#include "../includes/minishell.h"

char	*ft_trim(char *str)
{
	int		start;
	int		end;
	char	*ret;
	int		i;

	start = 0;
	while (str[start] && is_spaces(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= 0 && is_spaces(str[end]))
		end--;
	ret = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start <= end)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[start] = '\0';
	return (ret);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_spaces(str[i]) != 0)
			return (0);
	}
	return (1);
}
