/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 01:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count_env(envp) - 1)
	{
		j = 0;
		while (j < count_env(envp) - 1 - i)
		{
			if (envp[j][0] > envp[j + 1][0])
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	print_export(char **envp)
{
	int		i;
	char	*ptr;
	char	**envp_cpy;

	i = -1;
	envp_cpy = copy_env(envp, count_env(envp) + 1);
	if (!envp_cpy)
		return (EXIT_FAILURE);
	sort_export(envp_cpy);
	while (++i < count_env(envp_cpy))
	{
		ptr = envp_cpy[i];
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (*ptr && *ptr != '=')
			ft_putchar_fd(*ptr++, STDOUT_FILENO);
		if (*ptr == '=')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(ptr + 1, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	free_argv(&envp_cpy);
	return (EXIT_SUCCESS);
}

bool	is_valid_name(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (false);
	while (*s && *s != '=')
	{
		if (!ft_isalnum(*s) && *s != '_')
			return (false);
		s++;
	}
	return (true);
}

int	export_arg(char *s, char ***envp)
{
	int		len;
	char	**new_envp;

	len = count_env(*envp);
	new_envp = copy_env(*envp, len + 2);
	if (!new_envp)
		return (EXIT_FAILURE);
	new_envp[len] = ft_strdup(s);
	if (!new_envp[len])
	{
		free_argv(&new_envp);
		return (EXIT_FAILURE);
	}
	new_envp[len + 1] = NULL;
	free_argv(envp);
	*envp = new_envp;
	return (EXIT_SUCCESS);
}

int	export(char **argv, char ***envp)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!argv[1])
		return (print_export(*envp));
	while (argv[i])
	{
		if (!is_valid_name(argv[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			exit_code = 1;
		}
		else if (export_arg(argv[i], envp))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
