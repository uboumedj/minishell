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
		trim_command(sh);
		if (ft_strcmp(sh->command, "") != 0)
		{
			if (sh->arguments)
				replace_env_vars_and_tilde(sh);
			signal = try_builtin_command(sh);
			if (signal == 0)
			{
				if (search_command(sh) == 0)
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
	if (tab)
	{
		if (tab[0])
		{
			tmp_cmd = ft_strdup(tab[0]);
			sh->arguments = ft_strarrdup(tab);
		}
		else
			tmp_cmd = ft_strdup("");
		ft_strdel(&(sh->command));
		sh->command = tmp_cmd;
	}
	ft_strarrayfree(tab);
}

void	replace_env_vars_and_tilde(t_shell *sh)
{
	int		i;
	char	*tmp;
	char	*replaced_line;

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
		else if (needs_tilde_replacing(sh->arguments[i]))
		{
			replaced_line = replace_tilde(sh->env, sh->arguments[1]);
			ft_strdel(&(sh->arguments[i]));
			sh->arguments[i] = replaced_line;
		}
		i++;
	}
}

int		needs_tilde_replacing(char *argument)
{
	int		result;

	if (argument[0] == '~' && (!argument[1] || argument[1] == '/'))
		result = 1;
	else
		result = 0;
	return (result);
}

char	*replace_tilde(char **env, char *argument)
{
	char	*home;
	char	*result;

	home = env_key_value(env, "$HOME");
	if (!argument[1])
		result = home;
	else
	{
		result = ft_strjoin(home, &argument[1]);
		ft_strdel(&home);
	}
	return (result);
}
