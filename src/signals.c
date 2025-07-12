/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:36:43 by piyu              #+#    #+#             */
/*   Updated: 2025/07/11 23:15:59 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler(int signum)
{
	g_signal = signum;
}

int	readline_handler(void)
{
	if (g_signal == SIGINT)
	{
		get_info()->exit_code = 128 + g_signal;
		g_signal = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_redisplay();
	}
	return (0);
}

int	rl_heredoc_handler(void)
{
	if (g_signal == SIGINT)
	{
		get_info()->exit_code = 128 + g_signal;
		rl_done = 1;
	}
	return (0);
}

static void	get_return_status(t_info *info, int status)
{
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		info->exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dump)", STDERR_FILENO);
		if (WTERMSIG(status) == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
		info->exit_code = EXIT_SUCCESS;
}

void	wait_call(t_info *info, pid_t last_pid)
{
	int		status;
	pid_t	pid;

	if (last_pid == 0)
	{
		while (waitpid(-1, NULL, WNOHANG) != -1)
			;
		return ;
	}
	while (1)
	{
		pid = wait(&status);
		if (pid == last_pid)
			get_return_status(info, status);
		if (pid == -1)
			return ;
	}
}
