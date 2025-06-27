/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 03:06:34 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 04:15:46 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quoted_heredoc(char *value)
{
	int	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static char	*expand_heredoc_value(char *value, t_info *info)
{
	int		total_len;

	total_len = ft_strlen(value);
	remove_quotes(value, 0, 0);
	return (value);
}

t_token	*save_heredoc(t_info *info, t_cmd *cmd, t_token *token)
{
	t_redir			*redir;

	redir = allocate_and_connect_redir(info, cmd);
	if (is_quoted_heredoc(token->value))
		redir->type = REDIR_HEREDOC_QUOTE;
	else
		redir->type = REDIR_HEREDOC;
	redir->file = expand_heredoc_value(token->value, info);
	return (token->next);
}

t_token	*save_redirection(t_info *info, t_cmd *cmd, t_token *token)
{
	t_redir			*redir;

	redir = allocate_and_connect_redir(info, cmd);
	if (is_ambiguous_redir(token->next, info))
		return (redir->type = REDIR_AMB, redir->file = token->next->value, cmd->is_error = 1, token->next);
	if (token->type == IN)
		redir->type = REDIR_INPUT;
	else if (token->type == OUT)
		redir->type = REDIR_OUTPUT;
	else if (token->type == APPEND)
		redir->type = REDIR_APPEND;
	redir->file = expand_value(token->next->value, info);
	return (token->next);
}
