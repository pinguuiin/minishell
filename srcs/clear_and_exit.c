/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 02:04:34 by piyu              #+#    #+#             */
/*   Updated: 2025/06/27 02:18:22 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char *s1, char *s2, char *s3, int exit_code)
{
	error_msg(s1, s2, s3, exit_code);
	arena_free_all(get_info()->arena);
	exit(exit_code);
}

int	error_msg(char *s1, char *s2, char *s3, int exit_code)
{
	get_info()->exit_code = exit_code;
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
	return (exit_code);
}

void	clean_and_exit(char *err_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(" :couldn't allocate memory", STDERR_FILENO);
	arena_free_all(get_info()->arena);
	exit(1);
}
