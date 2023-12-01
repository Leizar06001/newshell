/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:20:36 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:21:22 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var_in_str(char *str, int pos, char *name, char *val)
{
	char	*ret;
	int		i;
	int		j;
	int		s;

	ret = malloc(sizeof(char) * (ft_strlen(str)
				- ft_strlen(name) + ft_strlen(val) + 2));
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

	start = ft_strchr(str, '$') + 1;
	end = start - str;
	while (str[++end])
	{
		if (is_alpha_num(str[end]) == 0)
			break ;
	}
	var_name = ft_strldup(start, end - (int)(start - str));
	var_val = get_env_var(var_name, g_data.copy_env);
	if (var_val)
		ret = replace_var_in_str(str, start - str - 1, var_name, var_val);
	else
		ret = replace_var_in_str(str, start - str - 1, var_name, "");
	free(var_name);
	return (ret);
}

char	**replace_vars(char **args)
{
	int		i;
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
