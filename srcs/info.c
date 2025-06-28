/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/06/28 05:26:38 by piyu             ###   ########.fr       */
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

void	reset_info()
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
