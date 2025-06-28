/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 03:32:56 by piyu              #+#    #+#             */
/*   Updated: 2025/06/28 05:08:58 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_ind(char **envp, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && (*(envp[i] + len) == '='
		|| *(envp[i] + len) == '\0'))
			return (i);
		i++;
	}
	return (i);
}

/*Find PATH in the environment variables and split it into a 2d array*/
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
		exec_exit("minishell", cmd, "Couldn't allocate memory", 1);
	return (prefix);
}

/*Concatenate paths and filename and check the existence and
accessability of the target file*/
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
		exec_exit("minishell", cmd, "Couldn't allocate memory", 1);
	while (prefix[i])
	{
		path = arena_strjoin(&info->arena, prefix[i], slash_cmd);
		if (!path)
			exec_exit("minishell", cmd, "Couldn't allocate memory", 1);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == -1)
				exec_exit("minishell", cmd, "Permission denied", 126);
			return (path);
		}
		i++;
	}
	exec_exit("minishell", cmd, "No such file or directory", 127);
	return (NULL);
}

/*Check if command has absolute/relative path or no path and then execute it*/
void	execute_command(t_info *info, char **argv)
{
	char	*filepath;

	if (ft_isalpha(argv[0][0]))
		filepath = find_cmdfile(info, argv[0]);
	else
	{
		filepath = argv[0];
		if (access(filepath, F_OK) == -1)
			exec_exit("minishell", filepath, "No such file or directory", 127);
		if (access(filepath, F_OK) == 0 && access(filepath, X_OK) == -1)
			exec_exit("minishell", filepath, "Permission denied", 126);
	}
	if (execve(filepath, argv, info->env_arr) == -1)
	{
		if (argv[1])
			exec_exit(filepath, NULL, argv[1], 126);
		else
			exec_exit("minishell", NULL, filepath, 126);
	}
}
