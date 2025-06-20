/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:58:24 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_update_env(char **envp, int j)
{
	int	i;

	i = j;
	while (envp[i])
	{
		if (i == j)
		{
			free(envp[j]);
			envp[j] = NULL;
		}
		envp[i] = envp[i + 1];
		i++;
	}
}

int	unset(char **argv, char **envp)
{
	int	i;
	int	j;

	i = 0;
	if (!argv[1])
		return (EXIT_SUCCESS);
	if (argv[1][0] == '-')
	{
		ft_putstr_fd("unset: ", STDERR_FILENO);
		ft_putchar_fd(argv[1][0], STDERR_FILENO);
		if (argv[1][1])
			ft_putchar_fd(argv[1][1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		return (2);
	}
	while (argv[++i])
	{
		j = get_env_ind(envp, argv[i]);
		if (envp[j])
			unset_update_env(envp, j);
	}
	return (EXIT_SUCCESS);
}
