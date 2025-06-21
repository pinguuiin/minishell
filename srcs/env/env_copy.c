/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:17:13 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 13:11:02 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_envp(char **envp)
{
	size_t count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

static char	**copy_envp_entries(char **envp, char **envp_copy, int envp_num, t_info *info)
{
	int	i;

	i = 0;
	while (i < envp_num)
	{
		envp_copy[i] = aalloc(&(info->arena), ft_strlen(envp[i]) + 1);
		if (!envp_copy[i])
		{
			ft_putstr_fd("fails memory allocation for envp_copy entry\n", STDERR_FILENO);
			arena_free_all(info->arena);
			exit(1);
		}
		ft_strlcpy(envp_copy[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

char	**copy_envp(char **envp, t_info *info)
{
	char	**envp_copy;
	int		envp_num;

	envp_num = count_envp(envp);
	envp_copy = aalloc(&(info->arena), (envp_num + 1) * sizeof(char *));
	if (!envp_copy)
	{
		ft_putstr_fd("fails memory allocation for envp_copy\n", STDERR_FILENO);
		arena_free_all(info->arena);
		exit(1);
	}
	envp_copy = copy_envp_entries(envp, envp_copy, envp_num, info);
	return (envp_copy);
}
