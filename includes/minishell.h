/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 23:14:16 by piyu             ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "memory.h"
# include "validation.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"

typedef struct s_info
{
	t_arena		*arena;
	t_token		*tokens;
	t_env		*env_list;
	t_cmd		*cmds;			// Linked list of piped commands
	char		**env_arr;
	int			exit_code;
<<<<<<< HEAD
	int			cmd_count;		// Number of commands in pipeline
	int			pipefd[2];
=======
	int			cmd_num;		// Number of commands in pipeline
	char		*input;

>>>>>>> 68e064d (Add dirty heredoc code)
}	t_info;

void	init_info(char **envp);
t_info	*get_info(void);
void	reset_info(void);

void	close_fds(t_cmd *cmds);
void	exec_exit(char *s1, char *s2, char *s3, int exit_code);
int		error_msg(char *s1, char *s2, char *s3, int exit_code);
void	clean_and_exit(char *err_msg);

int		get_return_status(t_info *info, pid_t pid);

#endif
