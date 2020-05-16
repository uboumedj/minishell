/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char		**delete_from_env(char **env, char *key)
{
	int		i;
	int		j;
	int		key_index;
	char	**new_env;

	i = 0;
	j = 0;
	key_index = search_env(env, key);
	new_env = NULL;
	if (key_index != -1)
	{
		if (!(new_env = malloc(sizeof(char*) * (ft_strarraylen(env)))))
			return (NULL);
		while (env[i])
		{
			if (i != key_index)
			{
				new_env[j] = ft_strdup(env[i]);
				j++;
			}
			i++;
		}
		new_env[j] = NULL;
	}
	return (new_env);
}

char		**add_to_env(char **env, char *key, char *value)
{
	int		key_index;
	char	*temp_line;
	char	*line;
	char	**new_env;

	key_index = search_env(env, key);
	temp_line = ft_strjoin(key, "=");
	line = ft_strjoin(temp_line, value);
	ft_strdel(&temp_line);
	if (key_index != -1)
	{
		new_env = ft_strarrdup(env);
		ft_strdel(&(new_env[key_index]));
	}
	else
	{
		if (!(new_env = malloc(sizeof(char*) * (ft_strarraylen(env) + 2))))
			return (NULL);
		while (env[++key_index])
			new_env[key_index] = ft_strdup(env[key_index]);
		new_env[key_index + 1] = NULL;
	}
	new_env[key_index] = ft_strdup(line);
	ft_strdel(&line);
	return (new_env);
}
