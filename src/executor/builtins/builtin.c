/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:23:59 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 05:26:11 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getpwd(char **buf, char **envp)
{
	char	*bufcpy;

	*buf = getcwd(NULL, 0);
	if (*buf)
	{
		bufcpy = arena_strjoin(&get_info()->arena, *buf, "");
		free(*buf);
		if (!bufcpy)
			clean_and_exit("pwd");
		*buf = bufcpy;
		return (0);
	}
	*buf = envp[get_env_ind(envp, "PWD")];
	if (*buf && ft_strchr(*buf, '='))
	{
		*buf += 4;
		return (0);
	}
	return (1);
}

static int	pwd(char **argv, char **envp)
{
	char	*buf;

	if (argv[1] && argv[1][0] == '-' && argv[1][1])
		return (error_msg("minishell: pwd", argv[1], "invalid option", 2));
	if (getpwd(&buf, envp))
	{
		error_msg("minishell", "pwd", "error retrieving current directory", 1);
		return (1);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (0);
}

static int	env(char **argv, char **envp)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		ft_putstr_fd("env: '", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd("': No such file or directory", STDERR_FILENO);
		return (127);
	}
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

bool	is_builtin(t_cmd *cmds)
{
	char	*cmd;

	if (!cmds->argv)
		return (false);
	cmd = cmds->argv[0];
	if (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0 || ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_info *info, char **argv)
{
	char	*cmd;

	cmd = argv[0];
	if (ft_strncmp(cmd, "echo", 5) == 0)
		info->exit_code = echo(argv);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		info->exit_code = cd(argv, info->env_arr);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		info->exit_code = pwd(argv, info->env_arr);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		info->exit_code = export(argv, &info->env_arr);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		info->exit_code = unset(argv, info->env_arr);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		info->exit_code = env(argv, info->env_arr);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		info->exit_code = shell_exit(info, argv);
	return (info->exit_code);
}
