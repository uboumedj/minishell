/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		try_path_command(t_shell *sh)
{
	char	**paths;
	char	*try_path;
	char	*try_command;
	int		i;
	int		found;

	paths = get_path_list(sh->env);
	i = 0;
	found = 0;
	while (paths[i] && !found)
	{
		try_path = ft_strjoin(paths[i], "/");
		try_command = ft_strjoin(try_path, sh->command);
		ft_strdel(&try_path);
		if (access(try_command, F_OK) == 0)
		{
			execute_command(sh, try_command);
			found = 1;
		}
		ft_strdel(&try_command);
		i++;
	}
	ft_strarrayfree(paths);
	return (found);
}

char	**get_path_list(char **env)
{
	char	*env_path;
	char	**paths;

	env_path = env_key_value(env, "$PATH");
	paths = ft_strsplit(env_path, ':');
	ft_strdel(&env_path);
	return (paths);
}

int		execute_command(t_shell *sh, char *cmd)
{
	pid_t	child_pid;
	int		child_status;

	child_pid = fork();
	if (child_pid < 0)
	{
		error_fork(child_pid);
		exit(-1);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd, sh->arguments, sh->env) < 0)
			return (-1);
		else
			exit(0);
	}
	wait(&child_status);
	return ((child_status < 0) ? -1 : 0);
}
