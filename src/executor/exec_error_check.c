/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 06:06:27 by piyu              #+#    #+#             */
/*   Updated: 2025/07/03 23:22:58 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_empty_string(t_info *info, t_cmd *cmds)
{
	int	is_empty;

	// if (cmds->argv == NULL)
	// 	printf("IS NULL\n");
	// else if (cmds->argv[0] == NULL)
	// 	printf("argv[0] Is Null\n");
	// else if (cmds->argv[0][0] == '\0')
	// 	printf("argv[0][0] is null\n");
	// else
	// 	printf("None of them\n");
	// return (true);
	is_empty = 0;
	if (!cmds->argv)
		is_empty = 1;
	if (is_empty && cmds->is_error)
	{
		ft_putendl_fd("Command '' not found", STDERR_FILENO);
		return (info->exit_code = 127, true);
	}
	else if (is_empty && !cmds->is_error)
		return (true);
	return (false);
}

static bool	has_only_dots(t_info *info, t_cmd *cmds)
{
	if (ft_strncmp(cmds->argv[0], "..", 3) == 0)
	{
		ft_putendl_fd("..: command not found", STDERR_FILENO);
		return (info->exit_code = 127, true);
	}
	else if (ft_strncmp(cmds->argv[0], ".", 2) == 0)
	{
		ft_putendl_fd("minishell: .: filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		return (info->exit_code = 2, true);
	}
	return (false);
}

static bool	is_directory(t_cmd *cmds)
{
	struct stat	buf;

	if (stat(cmds->argv[0], &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		error_msg("minishell", cmds->argv[0], "Is a directory", 126);
		return (true);
	}
	return (false);
}

int	execution_error_check(t_info *info, t_cmd *cmds)
{
	if (has_empty_string(info, cmds) || has_only_dots(info, cmds)
	|| is_directory(cmds))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
