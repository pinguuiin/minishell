/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:53:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/28 21:20:57 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	save_cmd(t_info *info, t_cmd *cmd, t_token *token)
{
	char	*expanded_value;
	char	**divided_value;
	int		i;

	expanded_value = expand_value(token->value, info, cmd);
	divided_value = divide_by_delimiter(expanded_value, info);
	i = 0;
	while (divided_value[i])
	{
		add_to_argv(cmd, divided_value[i++], info);
	}
}

static t_token	*save_heredoc(t_info *info, t_cmd *cmd, t_token *token)
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

static t_token	*save_redirection(t_info *info, t_cmd *cmd, t_token *token)
{
	t_redir			*redir;

	redir = allocate_and_connect_redir(info, cmd);
	if (is_ambiguous_redir(token->next, info, cmd))
		return (redir->type = REDIR_AMB, redir->file = token->next->value, cmd->is_error = 1, token->next);
	if (token->type == IN)
		redir->type = REDIR_INPUT;
	else if (token->type == OUT)
		redir->type = REDIR_OUTPUT;
	else if (token->type == APPEND)
		redir->type = REDIR_APPEND;
	redir->file = expand_value(token->next->value, info, cmd);
	return (token->next);
}

void	parser(t_info *info)
{
	t_token		*token;
	t_cmd		*cmd;

	token = info->tokens;
	(info->cmd_num)++;
	cmd = aalloc(&(info->arena), sizeof(t_cmd));
	if (!cmd)
		clean_and_exit("cmd");
	info->cmds = cmd;
	while (token)
	{
		if (token->type == PIPE)
			cmd = allocate_and_connect_cmd(info, cmd);
		else if (token->type == CMD)
			save_cmd(info, cmd, token);
		else if (token->type == HEREDOC)
			token = save_heredoc(info, cmd, token);
		else
			token = save_redirection(info, cmd, token);
		token = token->next;
	}
}
