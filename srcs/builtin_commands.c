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

void	builtin_echo(t_shell *sh)
{
	int		i;

	i = 0;
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
