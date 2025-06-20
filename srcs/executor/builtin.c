/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:23:59 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:28:05 by piyu             ###   ########.fr       */
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

bool	is_n_flag(char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-')
		return (false);
	while (s[i] == 'n')
		i++;
	if (i == 1 || s[i])
		return (false);
	return (true);
}

int	echo(char **argv)
{
	int		i;
	bool	newline;

	i = 1;
	newline = 1;
	if (is_n_flag(argv[1]))
		newline = 0;
	while (is_n_flag(argv[i]))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
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

int	execute_builtin(t_alloc *data, char **argv)
{
	char	*cmd;
	int		exec_status;

	cmd = argv[0];
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		exec_status = echo(argv);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		exec_status = cd(argv, data->env);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		exec_status = pwd(argv);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		exec_status = export(argv, &data->env);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		exec_status = unset(argv, data->env);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		exec_status = env(argv, data->env);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		exec_status = shell_exit(argv);
	else
		exec_status = -1;
	return (exec_status);
}
