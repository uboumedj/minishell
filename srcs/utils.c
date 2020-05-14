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

void	update_pwd(t_shell *sh, char *path)
{
	int		pwd;
	int		old_pwd;

	pwd = search_env(sh->env, "PWD=");
	old_pwd = search_env(sh->env, "OLDPWD=");
	free(sh->env[old_pwd]);
	sh->env[old_pwd] = ft_strjoin("OLDPWD=", &(sh->env[pwd][4]));
	free(sh->env[pwd]);
	sh->env[pwd] = ft_strjoin("PWD=", path);
}

int		search_env(char **env, char *key)
{
	int		i;
	int		j;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j] == key[j] && key[j] != 0)
				j++;
			if (key[j] == 0)
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*env_key_value(char **env, char *key)
{
	int		index;
	char	*val;
	int		success;

	success = 0;
	if (env && env[0] && key && key[0])
	{
		index = search_env(env, &key[1]);
		if (index >= 0)
		{
			val = ft_strdup(&(env[index][ft_strlen(key)]));
			success = 1;
		}
	}
	if (success == 0)
		val = ft_strdup("");
	return (val);
}
