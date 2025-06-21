/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:23:43 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 16:21:31 by donheo           ###   ########.fr       */
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
	info->error_code = 0;
	info->envp_copy = envp_copy(envp, info);
}

