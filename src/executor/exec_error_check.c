/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 06:06:27 by piyu              #+#    #+#             */
/*   Updated: 2025/07/11 23:20:08 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_empty_string(t_info *info, t_cmd *cmds)
{
	if (!cmds->argv)
		return (true);
	if (cmds->argv[0][0] == '\0')
	{
		ft_putendl_fd("Command '' not found", STDERR_FILENO);
		return (info->exit_code = 127, true);
	}
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
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		return (info->exit_code = 2, true);
	}
	return (false);
}

static bool	is_directory(t_cmd *cmds)
{
	struct stat	buf;

	if (!ft_strchr(cmds->argv[0], '/'))
		return (false);
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
		return (1);
	return (0);
}
