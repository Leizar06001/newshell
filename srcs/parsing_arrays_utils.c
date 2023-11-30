#include "../includes/minishell.h"

char **add_str_arr_pos(char **arr, int pos, char *str)
{
	int		i;
	int		len;
	char	**ret;

	// printf("ADD LINE: %s\n", str);
	len = 0;
	while (arr[len])
		len++;
	// printf("Actual len: %d, Malloc size: %d\n", len, len + 2);
	ret = malloc(sizeof(char *) * (len + 2));
	i = -1;
	if (pos > len)
		pos = len;
	while (++i < pos){
		ret[i] = arr[i];
		// printf("copy line %s at %d\n", arr[i], i);
	}
	ret[i] = str;
	// printf("insert line %s at %d\n", str, i);
	while (++i <= len){
		ret[i] = arr[i - 1];
		// printf("copy line -1 %s at %d\n", arr[i - 1], i);
	}
	ret[i] = NULL;
	// printf("> New length: %d, NULL at %d\n\n", len + 2, i);
	return (ret);
}

char **add_str_part_to_arr(char **args, char *str, int start, int end)
{
	char	*extract;
	char	**ret;

	if (end > (int)ft_strlen(str))
		end = ft_strlen(str);
	if (start >= end)
		return (args);
	extract = ft_strldup(str + start, end - start + 1);
	ret = add_str_arr_pos(args, 9999999, extract);
	free(args);
	return (ret);
}

char	**rm_arr_line(char **args, int pos)
{
	// printf("Removing line %d: '%s'\n", pos, args[pos]);
	free(args[pos]);
	while (args[pos + 1])
	{
		args[pos] = args[pos + 1];
		pos++;
	}
	args[pos] = NULL;
	return (args);
}
