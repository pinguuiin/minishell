/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:06:09 by piyu              #+#    #+#             */
/*   Updated: 2025/06/24 21:45:35 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	realloc_env_var(char **var, char *name, char *content)
{
	t_info	*info;

	info = get_info();
	*var = aalloc(&info->arena, ft_strlen(name) + ft_strlen(content) + 2);
	if (!*var)
		return (error_msg("minishell", "cd", "Couldn't allocate memory", 1));
	ft_memmove(*var, name, ft_strlen(name));
	ft_memmove(*var + ft_strlen(name), "=", 1);
	ft_memmove(*var + ft_strlen(name) + 1, content, ft_strlen(content));
	(*var)[(ft_strlen(name) + ft_strlen(content) + 1)] = '\0';
	return (EXIT_SUCCESS);
}

static int	update_env_pwd(char **envp, char *oldpwd, char *pwd)
{
	int	oldpwd_ind;
	int	pwd_ind;

	oldpwd_ind = get_env_ind(envp, "OLDPWD");
	pwd_ind = get_env_ind(envp, "PWD");
	if (envp[oldpwd_ind])
	{
		if (realloc_env_var(&envp[oldpwd_ind], "OLDPWD", oldpwd))
			return (EXIT_FAILURE);
	}
	if (envp[pwd_ind])
	{
		if (realloc_env_var(&envp[pwd_ind], "PWD", pwd))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cd(char **argv, char **envp)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*path;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (error_msg("minishell", NULL, "cd", 1));
	if (!argv[1])
	{
		path = envp[get_env_ind(envp, "HOME")];
		if (!path || !ft_strchr(path, '='))
			return (error_msg("minishell", "cd", "HOME not set", 1));
		path += ft_strlen("HOME") + 1;
	}
	else if (argv[2])
		return (error_msg("minishell", "cd", "too many arguments", 1));
	else
		path = argv[1];
	if (chdir(path) == -1)
		return (error_msg("minishell", NULL, "cd", 1));
	if (!getcwd(pwd, sizeof(pwd)))
		return (error_msg("minishell", NULL, "cd", 1));
	return (update_env_pwd(envp, oldpwd, pwd));
}
