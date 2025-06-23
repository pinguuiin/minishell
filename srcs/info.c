/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/06/23 04:47:12 by piyu             ###   ########.fr       */
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
	ft_memset(info, 0, sizeof(t_info));
	info->paths->cmd = 0;
	info->paths->prefix = 0;
	info->paths->path = 0;
	info->paths->slash_cmd = 0;
	info->arena = arena_create(ARENA_BLOCK_SIZE);
	info->envarr = copy_envp(envp, info);
}
