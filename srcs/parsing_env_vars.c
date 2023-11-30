#include "../includes/minishell.h"

char	*replace_var_in_str(char *str, int pos, char *name, char *val)
{
	char	*ret;
	int		i;
	int		j;
	int		s;

	ret = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(name) + ft_strlen(val) + 2));
	i = -1;
	while (++i < pos)
		ret[i] = str[i];
	s = i;
	j = -1;
	i--;
	while (val[++j])
		ret[++i] = val[j];
	s += ft_strlen(name);
	while (str[++s])
		ret[++i] = str[s];
	ret[i + 1] = '\0';
	return (ret);
}

char	*check_vars_in_str(char *str)
{
	char	*start;
	int		end;
	char	*var_name;
	char	*var_val;
	char	*ret;

	// printf("\nOld str: %s\n", str);
	start = ft_strchr(str, '$') + 1;
	end = start - str;
	while (str[++end])
	{
		if (is_alpha_num(str[end]) == 0)
			break ;
	}
	// printf("End pos: %d\n", end);
	var_name = ft_strldup(start, end - (int)(start - str));
	// printf("> var name: %s\n", var_name);
	var_val = get_env_var(var_name, g_data.copy_env);

	// printf("> var val: %s\n", var_val);
	if (var_val)
		ret = replace_var_in_str(str, start - str - 1, var_name, var_val);
	else
	{
		// printf("*** NO VAR ***\n");
		ret = replace_var_in_str(str, start - str - 1, var_name, "");
	}
	// printf("New str: %s\n\n", ret);
	free(var_name);
	return (ret);
}

char	**replace_vars(char **args)
{
	int	i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '\'')
		{
			while (ft_strchr(args[i], '$'))
			{
				tmp = check_vars_in_str(args[i]);
				free(args[i]);
				args[i] = tmp;
			}
		}
	}
	return (args);
}
