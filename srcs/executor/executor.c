/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:47:50 by piyu              #+#    #+#             */
/*   Updated: 2025/06/28 05:25:36 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========!Free memory and close fds before exit!========

static void	select_executor(t_info *info, t_cmd *cmds)
{
	if (is_builtin(cmds))
		exit(execute_builtin(info, cmds->argv));
	else
		execute_command(info, cmds->argv);
}

static bool	only_redir(t_cmd *cmds)
{
	if (cmds->argv[0] == "\0" && cmds->redirection->file)
		return (true);
	return (false);
}

int	run_single_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	if (redirect(cmds->redirection))
		return (EXIT_FAILURE);
	if (is_builtin(cmds))
		return (execute_builtin(info, cmds->argv));
	pid = fork();
	if (pid == -1)
		return (error_msg("minishell", NULL, "fork", 1));
	else if (pid == 0)
		execute_command(info, cmds->argv);
	else
		return (get_return_status(info, pid));
	return (EXIT_FAILURE);
}

int	run_last_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;

	if (redirect(cmds->redirection))
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (error_msg("minishell", NULL, "fork", 1));
	else if (pid == 0)
		select_executor(info, cmds);
	else
		return (get_return_status(info, pid));
	return (EXIT_FAILURE);
}

int	run_piped_command(t_info *info, t_cmd *cmds)
{
	pid_t	pid;
	int		pipefd[2];

	if (redirect(cmds->redirection))
		return (EXIT_FAILURE);
	if (pipe(pipefd) == -1)
		return (error_msg("minishell", NULL, "pipe", 1));
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		select_executor(info, cmds);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		return (EXIT_SUCCESS);
	}
	else
		return (error_msg("minishell", NULL, "fork", 1));
}

/*Execute command in child process and wait in parent process*/
int	executor(t_info *info, t_cmd *cmds)
{
	// edge cases
	if (!cmds->next)
		return (run_single_command(info, cmds));
	while (cmds->next)
	{
		if (run_piped_command(info, cmds))
			return (EXIT_FAILURE);
		cmds = cmds->next;
	}
	return (run_last_command(info, cmds));
}
