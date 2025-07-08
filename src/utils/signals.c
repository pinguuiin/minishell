/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:36:43 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 04:38:23 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler(int signum)
{
	g_signal = signum;
}

// void	disable_printting_quit(void)
// {
// 	struct termios	tc;

// 	if (tcgetattr(STDIN_FILENO, &tc) == 0)
// 	{
// 		tc.c_cc[VQUIT] = _POSIX_VDISABLE;
// 		tcsetattr(STDIN_FILENO, TCSANOW, &tc);
// 	}
// }

void	get_return_status(t_info *info, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		info->exit_code = 128 + WTERMSIG(status);
	else
		info->exit_code = EXIT_SUCCESS;
}
