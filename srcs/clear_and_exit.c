/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(char ***argv)
{
	int i;

	i = 0;
	if (!*argv)
		return ;
    while ((*argv)[i])
	{
        free((*argv)[i]);
		i++;
	}
    free(*argv);
	*argv = NULL;
}

void	free_path_elem(t_path *paths)
{
	if (!paths)
		return ;
	if (paths->cmd)
		free_argv(&(paths->cmd));
	if (paths->prefix)
		free_argv(&(paths->prefix));
	if (paths->path)
	{
		free(paths->path);
		paths->path = NULL;
	}
	if (paths->slash_cmd)
	{
		free(paths->slash_cmd);
		paths->slash_cmd = NULL;
	}
	free(paths);
}

void	error_path_exit(t_alloc *data, char *s, int sys_error_flag)
{
	if (sys_error_flag == 0)
	{
		ft_putendl_fd(s, STDERR_FILENO);
		free_path_elem(data->paths);
		exit(EXIT_FAILURE);
	}
	else
	{
		perror(s);
		free_path_elem(data->paths);
		exit(sys_error_flag);
	}
}

int	error_return(char *s, int sys_error_flag)
{
	if (sys_error_flag == 0)
	{
		ft_putendl_fd(s, STDERR_FILENO);
		return(EXIT_FAILURE);
	}
	else
	{
		perror(s);
		return(sys_error_flag);
	}
}
