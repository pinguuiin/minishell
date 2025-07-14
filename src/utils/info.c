/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/07/15 00:34:45 by donheo           ###   ########.fr       */
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
	info->envp_arena = arena_create(ENV_BLOCK_SIZE);
	info->env_arr = copy_envp(envp, info->envp_arena);
}

void	reset_info(void)
{
	t_info	*info;
	t_arena	*arena;
	t_arena	*next;

	info = get_info();
	close_fds(info);
	free(info->input);
	arena = info->arena;
	while (arena)
	{
		next = arena->next;
		free(arena->memory);
		arena->memory = NULL;
		free(arena);
		arena = next;
	}
	info->tokens = NULL;
	info->env_list = NULL;
	info->cmds = NULL;
	info->input = NULL;
	info->cmd_count = 0;
	info->arena = arena_create(ARENA_BLOCK_SIZE);
}
