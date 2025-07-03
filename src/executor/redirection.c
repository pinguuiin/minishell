/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:39:02 by piyu              #+#    #+#             */
/*   Updated: 2025/07/03 17:33:34 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_redir *redir)
{
	if (redir->type == REDIR_INPUT)
		redir->fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUTPUT)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		redir->fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		redir->fd = open_heredoc(redir);
	if (redir->fd == -1)
		error_msg("minishell", NULL, redir->file, 1);
	return (redir->fd);
}

int	redirect(t_redir *redir)
{
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	while (redir)
	{
		if (redir->type == REDIR_AMB)
			return (error_msg("minishell", redir->file,
					"ambiguous redirect", 1));
		if (open_file(redir) == -1)
			return (EXIT_FAILURE);
		if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			fd[1] = redir->fd;
		else
			fd[0] = redir->fd;
		redir = redir->next;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
