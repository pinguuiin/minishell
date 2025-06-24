/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/06/25 00:57:57 by piyu             ###   ########.fr       */
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
	int			exit_code;
	t_env		*env;
	char		**envarr;
	t_cmd		*cmds;			// Linked list of piped commands
	int			num_cmds;		// Number of commands in pipeline
	t_arena		*arena;
	t_token		*tokens;

}	t_info;

void			init_info(char **envp);
t_info			*get_info(void);
void			exec_exit(char *s1, char *s2, char *s3, int exit_code);
int				error_msg(char *s1, char *s2, char *s3, int exit_code);
#endif
