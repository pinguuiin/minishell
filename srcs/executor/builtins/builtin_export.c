/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 01:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/06/25 00:59:19 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_export(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count_envp(envp) - 1)
	{
		j = 0;
		while (j < count_envp(envp) - 1 - i)
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

static int	print_export(char **envp)
{
	int		i;
	char	*ptr;
	char	**envp_cpy;

	i = -1;
	envp_cpy = copy_envp(envp, get_info());
	if (!envp_cpy)
		exec_exit("minishell", "export", "Couldn't allocate memory", 1);
	sort_export(envp_cpy);
	while (++i < count_envp(envp_cpy))
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
	return (EXIT_SUCCESS);
}

static bool	is_valid_name(char *s)
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

static void	export_arg(char *s, char ***envp)
{
	int		len;
	t_info	*info;
	char	**new_envp;

	info = get_info();
	len = count_envp(*envp);
	new_envp = aalloc(&info->arena, (len + 2) * sizeof(char *));
	if (!new_envp)
		exec_exit("minishell", "export", "Couldn't allocate memory", 1);
	new_envp = copy_envp_entries(envp, new_envp, len, info);
	new_envp[len] = arena_strjoin(&info->arena, s, "");
	if (!new_envp[len])
		exec_exit("minishell", "export", "Couldn't allocate memory", 1);
	new_envp[len + 1] = NULL;
	*envp = new_envp;
}

int	export(char **argv, char ***envp)
{
	int		i;
	t_info	*info;

	i = 1;
	info = get_info();
	if (!argv[1])
		return (print_export(*envp));
	while (argv[i])
	{
		if (!is_valid_name(argv[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			info->exit_code = 1;
		}
		export_arg(argv[i], envp);
		i++;
	}
	return (info->exit_code);
}
