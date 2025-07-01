/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/07/02 01:56:58 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_cmd *cmds)
{
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
}

void	silent_exit(int exit_code)
{
	get_info()->exit_code = exit_code;
	close_fds(get_info()->cmds);
	arena_free_all(get_info()->arena);
	exit(exit_code);
}

void	exec_exit(char *s1, char *s2, char *s3, int exit_code)
{
	error_msg(s1, s2, s3, exit_code);
	close_fds(get_info()->cmds);
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
	close_fds(info->cmds);
	info->exit_code = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(" :couldn't allocate memory", STDERR_FILENO);
	arena_free_all();
	exit(1);
}
