/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:23:59 by piyu              #+#    #+#             */
/*   Updated: 2025/06/24 21:14:44 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **argv)
{
	char	buf[PATH_MAX];

	if (argv[1] && argv[1][0] == '-' && argv[1][1])
	{
		ft_putendl_fd("pwd: invalid option", STDERR_FILENO);
		return (2);
	}
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (126);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	env(char **argv, char **envp)
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
	return (EXIT_SUCCESS);
}

bool	is_builtin(t_cmd *cmds)
{
	char	*cmd;

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
		info->exit_code = cd(argv, info->envarr);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		info->exit_code = pwd(argv);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		info->exit_code = export(argv, &info->envarr);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		info->exit_code = unset(argv, info->envarr);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		info->exit_code = env(argv, info->envarr);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		info->exit_code = shell_exit(info, argv);
	else
		info->exit_code = -1;
	return (info->exit_code);
}
