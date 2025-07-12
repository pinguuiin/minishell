/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:09:40 by piyu              #+#    #+#             */
/*   Updated: 2025/07/12 04:02:27 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	*trim_env_key(char *s);
int		get_env_ind(char **envp, char *name);

int		getpwd(char **buf, char **envp);
bool	is_builtin(t_cmd *cmds);
int		execute_builtin(t_info *info, char **argv);
int		cd(char **argv, char **envp);
int		echo(char **argv);
int		shell_exit(t_info *info, char **argv);
int		export(char **argv, char ***envp);
int		unset(char **argv, char **envp);

int		execution_error_check(t_info *info, t_cmd *cmds);
char	*arena_strjoin(t_arena **arena_ptr, char const *s1, char const *s2);
char	**arena_split(t_arena **arena_ptr, char const *s, char c);
void	execute_bin(t_info *info, char **argv);
void	executor(t_info *info, t_cmd *cmds);
int		open_heredoc(t_redir *redir);
int		redirect(t_redir *redir);

#endif
