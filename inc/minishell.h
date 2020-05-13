/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 18:32:20 by uboumedj          #+#    #+#             */
/*   Updated: 2019/10/05 17:03:53 by uboumedj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

# define EXIT_SIGNAL	-1

typedef struct			s_shell
{
	char				**env;
	char				*command;
	char				**arguments;
}						t_shell;

void					initialise_shell(t_shell *sh, char **env);
void					read_command(t_shell *sh);
void					print_prompt(void);
void					trim_command(t_shell *sh);
void					remove_tabs(char *str);
char					**save_arguments(char **tab);
int						try_builtin_command(t_shell *sh);

/*
** Builtin commands
*/

void					builtin_echo(t_shell *sh);
void					builtin_env(t_shell *sh);

/*
** Errors
*/

void					error_unknown(char *cmd);

#endif
