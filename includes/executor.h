/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:09:40 by piyu              #+#    #+#             */
/*   Updated: 2025/06/28 04:42:41 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/stat.h>
# include <fcntl.h>

int		get_env_ind(char **envp, char *name);
bool	is_builtin(t_cmd *cmds);
int		cd(char **argv, char **envp);
int		echo(char **argv);
int		unset(char **argv, char **envp);
int		export(char **argv, char ***envp);
int		shell_exit(t_info *info, char **argv);
int		execute_builtin(t_info *info, char **argv);
void	execute_command(t_info *info, char **argv);
int		executor(t_info *info, t_cmd *cmds);
char	*arena_strjoin(t_arena **arena_ptr, char const *s1, char const *s2);
char	**arena_split(t_arena **arena_ptr, char const *s, char c);
int		redirect(t_redir *redir);
#endif
