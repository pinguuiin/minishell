/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 15:38:21 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*get_info(void)
{
	static t_info	info;

	ft_memset(&info, 0, sizeof(t_info));
	return (&info);
}

void	init_info(char **envp)
{
	t_info	*info;

	info = get_info();
	info->arena = arena_create(ARENA_BLOCK_SIZE);
	info->envp_copy = copy_envp(envp, info);
}
