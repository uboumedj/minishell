/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_prompt(void)
{
	ft_putstr("\033[1;34m$> \033[0m");
}

void	remove_tabs(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

void	remove_quotations(t_shell *sh)
{
	char	*new_line;
	int		i;

	i = 0;
	while (sh->command[i])
	{
		if (sh->command[i] == '"' || sh->command[i] == '\'')
		{
			if (i > 0 && sh->command[i - 1] == '\\')
				new_line = str_with_index_removed(sh->command, i - 1);
			else
			{
				new_line = str_with_index_removed(sh->command, i);
				i = 0;
			}
			ft_strdel(&sh->command);
			sh->command = new_line;
			new_line = NULL;
		}
		else
			i++;
	}
}

char	*str_with_index_removed(char *str, int index)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(result = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	while (str[j])
	{
		if (j != index)
		{
			result[i] = str[j];
			i++;
		}
		j++;
	}
	result[i] = '\0';
	return (result);
}
