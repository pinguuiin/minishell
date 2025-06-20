/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 20:47:34 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"
# include "memory.h"
# include "validation.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"

typedef struct s_info
{
	int			error_code;
	t_env		*env;
	char		**envp_copy;
	t_cmd		*cmds;			// Linked list of piped commands
	int			num_cmds;		// Number of commands in pipeline
	t_arena		*arena;
	t_token		*tokens;

}	t_info;

void			init_info(char **envp);
t_info			*get_info(void);
void			free_argv(char ***argv);
void			free_path_elem(t_path *data);
void			error_path_exit(t_alloc *data, char *s, int sys_error_flag);
int				error_return(char *s, int sys_error_flag);
int				count_env(char **envp);
char			**copy_env(char **envp, int len);
int				init_execution(t_alloc *data, char **envp);
void			executor(t_command_line *cmd_line, t_alloc *data);
#endif
