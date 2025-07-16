/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/07/16 10:12:11 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_info *info)
{
	t_cmd	*cmds;

	cmds = info->cmds;
	while (cmds)
	{
		while (cmds->redirection)
		{
			if (cmds->redirection->fd != -1 && cmds->redirection->fd != -2)
				close(cmds->redirection->fd);
			cmds->redirection->fd = -1;
			cmds->redirection = cmds->redirection->next;
		}
		cmds = cmds->next;
	}
	if (info->fd_stdio[0] != -1)
		close(info->fd_stdio[0]);
	if (info->fd_stdio[1] != -1)
		close(info->fd_stdio[1]);
	info->fd_stdio[0] = -1;
	info->fd_stdio[1] = -1;
}

void	silent_exit(int exit_code)
{
	t_info	*info;

	info = get_info();
	info->exit_code = exit_code;
	close_fds(info);
	arena_free_all();
	exit(exit_code);
}

void	exec_exit(char *s1, char *s2, char *s3, int exit_code)
{
	t_info	*info;

	info = get_info();
	error_msg(s1, s2, s3, exit_code);
	close_fds(info);
	arena_free_all();
	exit(exit_code);
}

void	clean_and_exit(char *err_msg)
{
	t_info	*info;

	info = get_info();
	close_fds(info);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(" :couldn't allocate memory", STDERR_FILENO);
	arena_free_all();
	exit(1);
}
