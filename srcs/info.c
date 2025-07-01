/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 06:07:27 by donheo           ###   ########.fr       */
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
	info->arena = arena_create(ARENA_BLOCK_SIZE);
	info->env_arr = copy_envp(envp, info);
}

void	reset_info(void)
{
	t_info	*info;

	info = get_info();
	close_fds(info->cmds);
	info->tokens = NULL;
	info->env_list = NULL;
	info->cmds = NULL;
	info->exit_code = 0;
	info->cmd_num = 0;
}
