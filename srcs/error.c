/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_unknown(char *cmd)
{
	ft_putstr_fd("\033[1;31mcommand not found: \033[0m", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

void	error_path(char *path)
{
	ft_putstr_fd("\033[1;31mdirectory not found: \033[0m", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	error_file(char *path)
{
	struct stat data;

	lstat(path, &data);
	if (!(S_IFDIR & data.st_mode))
	{
		ft_putstr_fd("\033[1;31mcd: not a directory: \033[0m", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		error_permissions(path);
}

void	error_permissions(char *path)
{
	ft_putstr_fd("\033[1;31mcd: permission denied: \033[0m", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

void	error_fork(int pid)
{
	char	*pid_string;

	ft_putstr_fd("\033[1;31mFork failure for process: \033[0m", 2);
	pid_string = ft_itoa(pid);
	ft_putstr_fd(pid_string, 2);
	ft_strdel(&pid_string);
	ft_putstr_fd("\n", 2);
}
