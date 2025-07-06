/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 04:02:25 by piyu             ###   ########.fr       */
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
			if (cmds->redirection->fd == -1)
				break ;
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

int	error_msg(char *s1, char *s2, char *s3, int exit_code)
{
	get_info()->exit_code = exit_code;
	if (s1)
	{
		ft_putstr_fd(s1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (s2)
	{
		ft_putstr_fd(s2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(s3, STDERR_FILENO);
	}
	else
		perror(s3);
	return (exit_code);
}

void	clean_and_exit(char *err_msg)
{
	t_info	*info;

	info = get_info();
	info->exit_code = 1;
	close_fds(info);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(" :couldn't allocate memory", STDERR_FILENO);
	arena_free_all();
	exit(1);
}
