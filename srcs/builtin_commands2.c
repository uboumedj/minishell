/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_setenv(t_shell *sh)
{
	int		i;
	char	**new_env;

	i = 1;
	while (sh->arguments[i])
	{
		if (ft_strchr(sh->arguments[i], '=') == 0)
		{
			if (sh->arguments[i + 1])
			{
				new_env = add_to_env(sh->env, sh->arguments[i],
														sh->arguments[i + 1]);
				if (new_env)
				{
					ft_strarrayfree(sh->env);
					sh->env = new_env;
				}
				i++;
			}
		}
		else
			setenv_one_parameter(sh, sh->arguments[i]);
		i++;
	}
}

void	setenv_one_parameter(t_shell *sh, char *param)
{
	char	**splitted_param;
	char	**new_env;

	splitted_param = ft_strsplit(param, '=');
	new_env = NULL;
	if (splitted_param[0] && splitted_param[1])
		new_env = add_to_env(sh->env, splitted_param[0], splitted_param[1]);
	else if (splitted_param[0])
		new_env = add_to_env(sh->env, splitted_param[0], "");
	if (new_env)
	{
		ft_strarrayfree(sh->env);
		sh->env = new_env;
	}
	ft_strarrayfree(splitted_param);
}

void	builtin_unsetenv(t_shell *sh)
{
	char	**new_env;

	if (sh->arguments[1])
	{
		new_env = delete_from_env(sh->env, sh->arguments[1]);
		if (new_env)
		{
			ft_strarrayfree(sh->env);
			sh->env = new_env;
		}
	}
}

int		handle_exit(t_shell *sh, int signal)
{
	int		value;

	value = 0;
	if (signal == EXIT_SIGNAL)
	{
		if (sh->arguments && sh->arguments[1])
			value = (unsigned char)ft_atoi(sh->arguments[1]);
		if (value > 0)
			ft_putstr("exit\n");
	}
	if (sh->arguments)
		ft_strarrayfree(sh->arguments);
	sh->arguments = NULL;
	return (value);
}

void	update_pwd(t_shell *sh, char *path)
{
	int		pwd;
	int		old_pwd;

	pwd = search_env(sh->env, "PWD=");
	old_pwd = search_env(sh->env, "OLDPWD=");
	if (pwd == -1)
		missing_from_env(sh, "PWD", path);
	else
	{
		if (old_pwd == -1)
			missing_from_env(sh, "OLDPWD", &(sh->env[pwd][4]));
		else
		{
			free(sh->env[old_pwd]);
			sh->env[old_pwd] = ft_strjoin("OLDPWD=", &(sh->env[pwd][4]));
		}
		free(sh->env[pwd]);
		sh->env[pwd] = ft_strjoin("PWD=", path);
	}
}
