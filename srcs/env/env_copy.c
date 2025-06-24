/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:17:13 by donheo            #+#    #+#             */
/*   Updated: 2025/06/25 00:44:43 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp(char **envp)
{
	size_t	count;

	count = 0;
	if (!envp)
		return (0);
	while (envp[count])
		count++;
	return (count);
}

char	**copy_envp_entries(char **envp, \
	char **envarr, int envp_num, t_info *info)
{
	int	i;

	i = 0;
	while (i < envp_num)
	{
		envarr[i] = aalloc(&(info->arena), ft_strlen(envp[i]) + 1);
		if (!envarr[i])
			clean_and_exit("memory allocation failed for envarr entry"); //consistency?
		ft_strlcpy(envarr[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envarr[i] = NULL;
	return (envarr);
}

char	**copy_envp(char **envp, t_info *info)
{
	char	**envarr;
	int		envp_num;

	envp_num = count_envp(envp);
	envarr = aalloc(&(info->arena), (envp_num + 1) * sizeof(char *));
	if (!envarr)
		clean_and_exit("memory allocation failed for envarr"); //consistency?
	envarr = copy_envp_entries(envp, envarr, envp_num, info);
	return (envarr);
}
