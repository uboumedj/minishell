/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_shell		sh;
	char		exit_value;

	(void)argc;
	(void)argv;
	exit_value = 0;
	initialise_shell(&sh, env);
	exit_value = read_command(&sh);
	if (sh.command)
		free(sh.command);
	if (sh.arguments)
		ft_strarrayfree(sh.arguments);
	ft_strarrayfree(sh.env);
	return (exit_value);
}
