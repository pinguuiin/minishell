/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 03:32:56 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
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
static char	**find_path(t_alloc *data)
{
	char	*ptr;
	char	*path;
	char	**prefix;

	ptr = data->env[get_env_ind(data->env, "PATH")];
	if (!ptr || !ft_strchr(ptr, '='))
		error_path_exit(data, "Command not found: PATH not set", 127);
	ptr += ft_strlen("PATH") + 1;
	path = ft_strdup(ptr);
	if (!path)
		error_path_exit(data, "Couldn't allocate memory", 0);
	prefix = ft_split(path, ':');
	free(path);
	if (!prefix)
		error_path_exit(data, "Couldn't allocate memory", 0);
	return (prefix);
}

/*Concatenate paths and filename and check the existence and
accessability of the target file*/
static char	*find_cmdfile(t_alloc *data, t_path *paths, char *cmd)
{
	int	i;

	i = 0;
	paths->prefix = find_path(data);
	paths->slash_cmd = ft_strjoin("/", cmd);
	if (!paths->slash_cmd)
		error_path_exit(data, "Couldn't allocate memory", 0);
	while (paths->prefix[i])
	{
		paths->path = ft_strjoin(paths->prefix[i], paths->slash_cmd);
		if (!paths->path)
			error_path_exit(data, "Couldn't allocate memory", 0);
		if (access(paths->path, F_OK) == 0)
		{
			if (access(paths->path, X_OK) == -1)
				error_path_exit(data, cmd, 126);
			return (paths->path);
		}
		free(paths->path);
		paths->path = NULL;
		i++;
	}
	error_path_exit(data, cmd, 127);
	return (NULL);
}

/*Check if command has absolute/relative path or no path and then execute it*/
void	execute_command(t_alloc *data, char **argv)
{
	t_path	*paths;
	char	**envp;
	char	*filepath;

	paths = data->paths;
	envp = data->env;
	paths->cmd = argv;
	if (ft_isalpha(paths->cmd[0][0]))
		filepath = find_cmdfile(data, paths, paths->cmd[0]);
	else
	{
		filepath = paths->cmd[0];
		if (access(filepath, F_OK) == 0 && access(filepath, X_OK) == -1)
			error_path_exit(data, filepath, 126);
		if (access(filepath, F_OK | X_OK) != 0)
			error_path_exit(data, filepath, 127);
	}
	if (execve(filepath, paths->cmd, envp) == -1)
		error_path_exit(data, "Execution failed", 126);
}
