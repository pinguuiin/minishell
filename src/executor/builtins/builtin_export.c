/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 01:18:06 by piyu              #+#    #+#             */
/*   Updated: 2025/07/15 01:07:38 by donheo           ###   ########.fr       */
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
	envp_cpy = copy_envp(envp, get_info()->arena);
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
	return (0);
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

static void	export_arg(t_info *info, char *s, char ***envp)
{
	int		i;
	int		len;
	char	*key;
	char	**new_envp;

	new_envp = *envp;
	key = trim_env_key(s);
	if (!key)
		clean_and_exit("export");
	i = get_env_ind(*envp, key);
	len = count_envp(*envp);
	if ((*envp)[i] && !ft_strchr(s, '='))
		return ;
	if (!(*envp)[i])
	{
		new_envp = aalloc(&info->envp_arena, (len + 2) * sizeof(char *));
		if (!new_envp)
			clean_and_exit("export");
		new_envp = copy_envp_entries(*envp, new_envp, len, info->envp_arena);
		new_envp[len + 1] = NULL;
	}
	new_envp[i] = arena_strjoin(&info->envp_arena, s, "");
	if (!new_envp[i])
		clean_and_exit("export");
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
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			info->exit_code = 1;
		}
		export_arg(info, argv[i], envp);
		i++;
	}
	return (info->exit_code);
}
