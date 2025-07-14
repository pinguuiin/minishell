/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/07/06 04:07:26 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*get_info(void)
{
	static t_info	info;

	return (&info);
}

void	init_info(char **envp)
{
	t_info	*info;

	info = get_info();
	info->fd_stdio[0] = dup(STDIN_FILENO);
	info->fd_stdio[1] = dup(STDOUT_FILENO);
	info->arena = arena_create(ARENA_BLOCK_SIZE);
	info->env_arr = copy_envp(envp, info);
}

void	reset_info(void)
{
	t_info	*info;

	info = get_info();
	free(info->input);
	close_fds(info);
	info->tokens = NULL;
	info->env_list = NULL;
	info->cmds = NULL;
	info->input = NULL;
	info->cmd_count = 0;
}
