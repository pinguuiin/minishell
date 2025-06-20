/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:09:40 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirection;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_command_line
{
	t_cmd			*cmds;
	int				num_cmds;
}	t_command_line;

typedef struct s_path
{
	char			**cmd;
	char			**prefix;
	char			*slash_cmd;
	char			*path;
}	t_path;

typedef struct s_alloc
{
	t_path			*paths;
	char			**env;
	int				exit_code;
}	t_alloc;

int					get_env_ind(char **envp, char *name);
int					cd(char **argv, char **envp);
int					unset(char **argv, char **envp);
int					export(char **argv, char ***envp);
int					shell_exit(char **argv);
int					execute_builtin(char **argv, char ***envp);
void				execute_command(t_alloc *data, char **argv);
int					executor(char **argv, t_alloc *data);
#endif
