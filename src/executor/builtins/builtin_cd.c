/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:06:09 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 00:24:04 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	realloc_env_var(char **var, char *name, char *content)
{
	t_info	*info;

	info = get_info();
	*var = aalloc(&info->arena, ft_strlen(name) + ft_strlen(content) + 2);
	if (!*var)
		clean_and_exit("cd");
	ft_memmove(*var, name, ft_strlen(name));
	ft_memmove(*var + ft_strlen(name), "=", 1);
	ft_memmove(*var + ft_strlen(name) + 1, content, ft_strlen(content));
	(*var)[(ft_strlen(name) + ft_strlen(content) + 1)] = '\0';
}

static int	update_env_pwd(char **envp, char *oldpwd, char *pwd)
{
	int	oldpwd_ind;
	int	pwd_ind;

	oldpwd_ind = get_env_ind(envp, "OLDPWD");
	pwd_ind = get_env_ind(envp, "PWD");
	if (envp[oldpwd_ind])
		realloc_env_var(&envp[oldpwd_ind], "OLDPWD", oldpwd);
	if (envp[pwd_ind])
		realloc_env_var(&envp[pwd_ind], "PWD", pwd);
	return (0);
}

static char	*expand_path(char *path, char *pwd)
{
	char	*ptr;
	char	*parent_path;

	if (ft_strncmp(path, "..", 3))
		return (path);
	ptr = ft_strrchr(pwd, '/');
	parent_path = aalloc(&get_info()->arena, ptr - pwd + 2);
	if (!parent_path)
		clean_and_exit("cd");
	ft_strlcpy(parent_path, pwd, ptr - pwd + 2);
	return (parent_path);
}

int	cd(char **argv, char **envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*path;

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
	if (getpwd(&oldpwd, envp))
		return (error_msg("minishell", NULL, "cd", 1));
	if (chdir(expand_path(path, oldpwd)) == -1)
		return (error_msg("minishell", NULL, "cd", 1));
	if (getpwd(&pwd, envp))
		return (error_msg("minishell", NULL, "cd", 1));
	return (update_env_pwd(envp, oldpwd, pwd));
}
