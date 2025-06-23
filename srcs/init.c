/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:51:36 by piyu              #+#    #+#             */
/*   Updated: 2025/06/23 04:19:54 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

// char	**copy_env(char **envp, int len)
// {
// 	int		i;
// 	char	**arr;

// 	i = 0;
// 	arr = ft_calloc(len, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	while (i < count_env(envp))
// 	{
// 		arr[i] = ft_strdup(envp[i]);
// 		if (!arr[i])
// 		{
// 			free_argv(&arr);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

/*Initialize environment variables and variables to be malloced*/
// int	init_execution(t_info *info, char **envp)
// {
// 	info->paths = ft_calloc(1, sizeof(t_path));
// 	if (!info->paths)
// 		return (EXIT_FAILURE);

// 	info->envarr = copy_env(envp, count_env(envp) + 1);
// 	if (!info->env)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
