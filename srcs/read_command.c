/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_command(t_shell *sh)
{
	int		signal;

	signal = 0;
	while (signal != EXIT_SIGNAL)
	{
		print_prompt();
		get_next_line(0, &(sh->command));
		if (ft_strcmp(sh->command, "") != 0)
		{
			trim_command(sh);
			signal = try_builtin_command(sh);
			if (signal == 0)
				error_unknown(sh->command);
			if (sh->arguments)
				ft_strarrayfree(sh->arguments);
			sh->arguments = NULL;
		}
		ft_strdel(&(sh->command));
	}
}

void	print_prompt(void)
{
	ft_putstr("\033[1;34m&> \033[0m");
}

void	trim_command(t_shell *sh)
{
	char	*tmp_cmd;
	char	**tab;

	remove_tabs(sh->command);
	tab = ft_strsplit(sh->command, ' ');
	if (tab && tab[0])
	{
		tmp_cmd = ft_strdup(tab[0]);
		ft_strdel(&(sh->command));
		sh->command = tmp_cmd;
		if (tab[1])
			sh->arguments = save_arguments(tab);
	}
	ft_strarrayfree(tab);
}

char	**save_arguments(char **tab)
{
	char	**res;
	int		i;
	size_t	len;

	len = 1;
	while (tab[len])
		len++;
	if (!(res = malloc(sizeof(char *) * len)))
		return (NULL);
	i = 1;
	while (tab && tab[i])
	{
		res[i - 1] = ft_strdup(tab[i]);
		i++;
	}
	res[i - 1] = NULL;
	return (res);
}

int		try_builtin_command(t_shell *sh)
{
	if (ft_strcmp("echo", sh->command) == 0)
		builtin_echo(sh);
	else if (ft_strcmp("env", sh->command) == 0)
		builtin_env(sh);
	else if (ft_strcmp("exit", sh->command) == 0)
		return (-1);
	else
		return (0);
	return (1);
}
