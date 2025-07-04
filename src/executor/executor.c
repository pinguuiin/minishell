/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:47:50 by piyu              #+#    #+#             */
/*   Updated: 2025/07/03 22:41:12 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========!Free memory and readlines; close pipe and fds before exit!========

static void	select_executor(t_info *info, t_cmd *cmds)
{
	if (redirect(cmds->redirection))
		exit(info->exit_code);
	if (execution_error_check(info, cmds))
		exit(info->exit_code);
	if (is_builtin(cmds))
		exit(execute_builtin(info, cmds->argv));
	else
		execute_command(info, cmds->argv);
}

static int	run_single_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	if (is_builtin(cmds))
	{
		if (redirect(cmds->redirection))
			return (info->exit_code);
		if (execution_error_check(info, cmds))
			return (info->exit_code);
		return (execute_builtin(info, cmds->argv));
	}
	pid = fork();
	if (pid == -1)
		return (error_msg("minishell", NULL, "fork", 1));
	else if (pid == 0)
		select_executor(info, cmds);
	else
		return (get_return_status(info, pid));
	return (EXIT_FAILURE);
}

static int	run_last_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error_msg("minishell", NULL, "fork", 1));
	else if (pid == 0)
		select_executor(info, cmds);
	else
		return (get_return_status(info, pid));
	return (EXIT_FAILURE);
}

//return type might need fix
static int	run_piped_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (error_msg("minishell", NULL, "pipe", 1));
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		select_executor(info, cmds);
		return (EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		get_return_status(info, pid);
		return (EXIT_SUCCESS);
	}
	else
		return (error_msg("minishell", NULL, "fork", 1));
}

int	executor(t_info *info, t_cmd *cmds)
{
	// edge cases
	if (!cmds->next)
		return (run_single_command(info, cmds));
	while (cmds->next)
	{
		run_piped_command(info, cmds);
		cmds = cmds->next;
	}
	return (run_last_command(info, cmds));
}
