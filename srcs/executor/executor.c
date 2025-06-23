/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:47:50 by piyu              #+#    #+#             */
/*   Updated: 2025/06/23 03:56:49 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========!Free cmds and info before exit!========

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

/*Execute command in child process and wait in parent process*/
void	executor(t_info *info, t_cmd **cmds)
{
	pid_t	pid;
	int		status;

	// Check if it's a builtin command first
	if ((*cmds)->next == NULL && is_builtin(*cmds) == 1)
		return (execute_builtin(info, (*cmds)->argv));
	while (*cmds)
	{
		pid = fork();
		if (pid == 0)
			select_executor(info, *cmds);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				return (128 + WTERMSIG(status));
			else
				return (EXIT_SUCCESS);
		}
		else
		{
			perror("Fork failed");
			return (EXIT_FAILURE);
		}
	}
}
