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
int						try_builtin_command(t_shell *sh);
int						search_env(char **env, char *key);
void					replace_env_vars_and_tilde(t_shell *sh);
char					*env_key_value(char **env, char *key);

/*
** Builtin commands
*/

void					builtin_echo(t_shell *sh);
void					builtin_env(t_shell *sh);
void					builtin_cd(t_shell *sh);
void					update_pwd(t_shell *sh, char *path);

/*
** Path commands
*/

int						try_path_command(t_shell *sh);
char					**get_path_list(char **env);
int						execute_command(t_shell *sh, char *cmd);

/*
** Errors
*/

void					error_unknown(char *cmd);
void					error_path(char *path);
void					error_file(char *path);
void					error_permissions(char *path);
void					error_fork(int pid);

#endif