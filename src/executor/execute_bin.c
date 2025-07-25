/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 03:32:56 by piyu              #+#    #+#             */
/*   Updated: 2025/07/12 04:17:58 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_path(t_info *info, char *cmd)
{
	char	*path;
	char	**prefix;

	path = info->env_arr[get_env_ind(info->env_arr, "PATH")];
	if (!path || !ft_strchr(path, '='))
		exec_exit("minishell", cmd, "No such file or directory", 127);
	path += ft_strlen("PATH") + 1;
	prefix = arena_split(&info->arena, path, ':');
	if (!prefix)
		clean_and_exit(cmd);
	return (prefix);
}

static char	*find_cmdfile(t_info *info, char *cmd)
{
	int		i;
	char	**prefix;
	char	*slash_cmd;
	char	*path;

	i = 0;
	prefix = find_path(info, cmd);
	slash_cmd = arena_strjoin(&info->arena, "/", cmd);
	if (!slash_cmd)
		clean_and_exit(cmd);
	while (prefix[i])
	{
		path = arena_strjoin(&info->arena, prefix[i], slash_cmd);
		if (!path)
			clean_and_exit(cmd);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == -1)
				exec_exit("minishell", cmd, "Permission denied", 126);
			return (path);
		}
		i++;
	}
	exec_exit(NULL, cmd, "command not found", 127);
	return (NULL);
}

void	execute_bin(t_info *info, char **argv)
{
	char	*filepath;

	if (!ft_strchr(argv[0], '/'))
		filepath = find_cmdfile(info, argv[0]);
	else
	{
		filepath = argv[0];
		if (access(filepath, F_OK) == -1)
			exec_exit("minishell", filepath, "No such file or directory", 127);
		if (access(filepath, F_OK) == 0 && access(filepath, X_OK) == -1)
			exec_exit("minishell", filepath, "Permission denied", 126);
	}
	close_fds(info);
	signal(SIGQUIT, SIG_DFL);
	if (execve(filepath, argv, info->env_arr) == -1)
	{
		if (argv[1])
			exec_exit(filepath, NULL, argv[1], 2);
		else
			exec_exit("minishell", NULL, filepath, 1);
	}
}
