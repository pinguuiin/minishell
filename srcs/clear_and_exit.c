/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/06/24 19:49:02 by piyu             ###   ########.fr       */
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

void	exec_exit(char *s1, char *s2, char *s3, int exit_code)
{
	t_info	*info;

	info = get_info();
	info->exit_code = exit_code;
	if (s1)
	{
		ft_putstr_fd(s1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (s2)
	{
		ft_putstr_fd(s2, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(s3, STDERR_FILENO);
	}
	else
		perror(s3);
	arena_free_all(info->arena);
	exit(exit_code);
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
