/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:47:50 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:09:53 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========!Free cmd_line and data before exit!========

int	select_executor(t_alloc *data, t_command_line *cmd_line)
{
	if (cmd_line->cmds->is_builtin)
		return (execute_builtin(data, cmd_line->cmds->argv));
	else
		execute_command(data, cmd_line->cmds->argv);
	return (EXIT_FAILURE); // or 0?
}

/*Execute command in child process and wait in parent process*/
void	executor(t_command_line *cmd_line, t_alloc *data)
{
	pid_t	pid;
	int		status;
	int		exit_code;
	int		i;

	// Check if it's a builtin command first
	if (cmd_line->num_cmds == 1 && cmd_line->cmds->is_builtin == 1)
		return (execute_builtin(cmd_line->cmds->argv, &data->env));
	i = 0;
	while (i++ < cmd_line->num_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_command(data, cmd_line->cmds->argv);
			return (EXIT_FAILURE);
		}
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
