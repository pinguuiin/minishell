/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:36:43 by piyu              #+#    #+#             */
/*   Updated: 2025/06/28 04:36:56 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_return_status(t_info *info, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		info->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		info->exit_code = 128 + WTERMSIG(status);
	else
		info->exit_code = EXIT_SUCCESS;
	return (info->exit_code);
}
