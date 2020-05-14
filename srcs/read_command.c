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
			if (sh->arguments)
				replace_env_vars_and_tilde(sh);
			signal = try_builtin_command(sh);
			if (signal == 0)
			{
				if (try_path_command(sh) == 0)
					error_unknown(sh->command);
			}
			if (sh->arguments)
				ft_strarrayfree(sh->arguments);
			sh->arguments = NULL;
		}
		ft_strdel(&(sh->command));
	}
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
		sh->arguments = tab;
	}
}

void	replace_env_vars_and_tilde(t_shell *sh)
{
	int		i;
	char	*tmp;

	i = 1;
	while (sh->arguments[i])
	{
		tmp = NULL;
		if (sh->arguments[i][0] == '$' && sh->arguments[i][1])
		{
			tmp = env_key_value(sh->env, sh->arguments[i]);
			ft_strdel(&(sh->arguments[i]));
			sh->arguments[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else if (ft_strcmp("~", sh->arguments[i]) == 0)
		{
			tmp = env_key_value(sh->env, "$HOME");
			ft_strdel(&(sh->arguments[i]));
			sh->arguments[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
}
