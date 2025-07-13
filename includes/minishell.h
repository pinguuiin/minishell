/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:19:00 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 22:50:47 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "memory.h"
# include "validation.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"

extern volatile sig_atomic_t	g_signal;

typedef struct s_info
{
	t_arena	*arena;
	t_token	*tokens;
	t_env	*env_list;
	t_cmd	*cmds;
	char	**env_arr;
	char	*input;
	int		exit_code;
	int		cmd_count;
	int		fd_stdio[2];
}	t_info;

void	init_info(char **envp);
t_info	*get_info(void);
void	reset_info(void);

void	close_fds(t_info *info);
void	silent_exit(int exit_code);
void	exec_exit(char *s1, char *s2, char *s3, int exit_code);
int		error_msg(char *s1, char *s2, char *s3, int exit_code);
void	clean_and_exit(char *err_msg);

void	signal_handler(int signum);
int		readline_handler(void);
int		rl_heredoc_handler(void);
void	wait_call(t_info *info, pid_t pid);

#endif
