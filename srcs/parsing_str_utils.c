#include "../includes/minishell.h"

char	*ft_trim(char *str)
{
	int		start;
	int		end;
	char	*ret;
	int		i;

	start = 0;
	// printf("TRIM: %s\n", str);
	while (str[start] && is_spaces(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= 0 && is_spaces(str[end]))
		end--;
	ret = malloc(sizeof(char) * (end - start + 3));
	i = 0;
	// printf("from %d to %d\n", start, end);
	while (start <= end)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_reduce_multiple_spaces(char *str)
{
	int	i;
	int	j;
	int	flag;

	// printf("REDUCE: %s\n", str);
	i = 0;
	j = -1;
	flag = 0;
	while (str[++j])
	{
		if (!is_spaces(str[j]))
		{
			str[i++] = str[j];
			flag = 0;
		}
		else
		{
			if (flag == 0)
				str[i++] = ' ';
			else
				j++;
			flag = 1;
		}
	}
	str[i] = '\0';
	return (str);
}
