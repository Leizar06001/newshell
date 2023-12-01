#include "../includes/minishell.h"

void	init_out_arr(char **args, t_data *datas)
{
	int	i;
	int	nb_cmds;

	i = -1;
	nb_cmds = 1;
	while (args[++i])
	{
		if (args[i][0] == '|' || args[i][0] == ';')
			nb_cmds++;
	}
	printf("THERE IS %d COMANDS\n", nb_cmds);
	datas->args_arr = malloc(sizeof(char **) * (nb_cmds * 2 + 1));
	i = -1;
	while (++i <= nb_cmds * 2)
		datas->args_arr[i] = NULL;
}

void	fill_one_line(char **args, char **arr, int start, int end)
{
	printf("Filling one line from [%d]%s to [%d]%s\n", start, args[start], end, args[end]);
}

void	fill_arr_lines(char **args, t_data *datas)
{
	int	i;
	int	start;
	int	line;

	line = 0;
	start = 0;
	i = -1;
	while (args[++i])
	{
		if ((args[i][0] == '|' || args[i][0] == ';') && i - start > 0)
		{
			fill_one_line(args, datas->args_arr[line], start, i - 1);
			start = i + 1;
		}
	}
	fill_one_line(args, datas->args_arr[line], start, i - 1);
}

void	create_output(char **args, t_data *datas)
{
	init_out_arr(args, datas);
	fill_arr_lines(args, datas);
}
