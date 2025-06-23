/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:09:40 by piyu              #+#    #+#             */
/*   Updated: 2025/06/23 03:31:32 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_path
{
	char	**cmd;
	char	**prefix;
	char	*slash_cmd;
	char	*path;
}	t_path;

// typedef struct s_alloc
// {
// 	t_path	*paths;
// 	char	**env;
// 	int		exit_code;
// }	t_info;

int		get_env_ind(char **envp, char *name);
bool	is_builtin(t_cmd *cmds);
int		cd(char **argv, char **envp);
int		echo(char **argv);
int		unset(char **argv, char **envp);
int		export(char **argv, char ***envp);
int		shell_exit(char **argv);
int		execute_builtin(t_info *info, char **argv);
void	execute_command(t_info *info, char **argv);
void	executor(t_info *info, t_cmd **cmds);
#endif
