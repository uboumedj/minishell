/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		try_builtin_command(t_shell *sh)
{
	if (ft_strcmp("echo", sh->command) == 0)
		builtin_echo(sh);
	else if (ft_strcmp("env", sh->command) == 0)
		builtin_env(sh);
	else if (ft_strcmp("cd", sh->command) == 0)
		builtin_cd(sh);
	else if (ft_strcmp("exit", sh->command) == 0)
		return (-1);
	else
		return (0);
	return (1);
}

void	builtin_echo(t_shell *sh)
{
	int		i;

	i = 1;
	if (sh->arguments)
	{
		while (sh->arguments[i])
		{
			ft_printf("%s", sh->arguments[i]);
			if (sh->arguments[i + 1])
				ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
	}
}

void	builtin_env(t_shell *sh)
{
	int		i;

	i = 0;
	if (sh->env)
	{
		while (sh->env[i])
		{
			ft_printf("%s\n", sh->env[i]);
			i++;
		}
	}
}

void	builtin_cd(t_shell *sh)
{
	char	*path;
	char	*cwd;
	char	buffer[2048 + 1];

	if (sh->arguments && sh->arguments[0])
	{
		path = sh->arguments[1];
		if (!access(path, F_OK))
		{
			if (chdir(path) == -1)
				error_file(path);
			else
			{
				if (!(cwd = getcwd(buffer, 2048)))
					error_permissions(path);
				update_pwd(sh, cwd);
			}
		}
		else
			error_path(path);
	}
}