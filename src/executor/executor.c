/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:47:50 by piyu              #+#    #+#             */
/*   Updated: 2025/07/12 04:18:17 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	select_executor(t_info *info, t_cmd *cmds)
{
	if (redirect(cmds->redirection))
		silent_exit(info->exit_code);
	if (execution_error_check(info, cmds))
		silent_exit(info->exit_code);
	if (is_builtin(cmds))
		silent_exit(execute_builtin(info, cmds->argv));
	else
		execute_bin(info, cmds->argv);
}

static void	run_single_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	if (is_builtin(cmds))
	{
		if (!redirect(cmds->redirection) && !execution_error_check(info, cmds))
			execute_builtin(info, cmds->argv);
		return ;
	}
	pid = fork();
	if (pid == -1)
		error_msg("minishell", NULL, "fork", 1);
	else if (pid == 0)
		select_executor(info, cmds);
	else
		wait_call(info, pid);
}

static void	run_last_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_msg("minishell", NULL, "fork", 1);
	else if (pid == 0)
		select_executor(info, cmds);
	else
		wait_call(info, pid);
}

//return type might need fix
static int	run_piped_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (error_msg("minishell", NULL, "pipe", 1));
	pid = fork();
	if (pid < 0)
		return (error_msg("minishell", NULL, "fork", 1));
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		select_executor(info, cmds);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

void	executor(t_info *info, t_cmd *cmds)
{
	if (!cmds->next)
	{
		run_single_command(info, cmds);
		return ;
	}
	while (cmds->next)
	{
		if (run_piped_command(info, cmds))
		{
			wait_call(info, 0);
			return ;
		}
		cmds = cmds->next;
	}
	run_last_command(info, cmds);
}
