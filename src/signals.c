/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:36:43 by piyu              #+#    #+#             */
/*   Updated: 2025/07/09 03:58:16 by piyu             ###   ########.fr       */
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
	t_info	*info;

	info = get_info();
	if (g_signal == SIGINT)
	{
		info->exit_code = 128 + g_signal;
		g_signal = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	if (g_signal == SIGQUIT)
	{
		printf("what??\n");
		info->exit_code = 128 + g_signal;
		g_signal = 0;
		ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		close_fds(info);
		arena_free_all();
		kill(getpid(), SIGQUIT);
	}
	return (0);
}

void	get_return_status(t_info *info, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_signal = WTERMSIG(status);
		info->exit_code = 128 + g_signal;
		if (g_signal == SIGQUIT)
			ft_putendl_fd("Quit (core dump)", STDERR_FILENO);
	}
	else
		info->exit_code = EXIT_SUCCESS;
}
