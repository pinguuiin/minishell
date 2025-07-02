/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:53:38 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 11:25:45 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_word_token(t_token *token, t_cmd *cmd, t_info *info)
{
	char	*expanded_value;
	char	**divided_value;
	int		i;

	expanded_value = expand_value(token->value, info, cmd);
	divided_value = divide_by_delimiter(expanded_value, info);
	i = 0;
	while (divided_value[i])
	{
		add_to_argv(divided_value[i++], cmd, info);
	}
}

void	process_heredoc_token(t_token *token, t_cmd *cmd, t_info *info)
{
	t_redir	*redir;

	redir = allocate_and_connect_redir(cmd, info);
	if (is_quoted_heredoc(token->value))
		redir->type = REDIR_HEREDOC_QUOTE;
	else
		redir->type = REDIR_HEREDOC;
	remove_quotes(token->value);
	redir->file = token->value;
}

static t_token	*process_redirection_token(t_token *token, \
t_cmd *cmd, t_info *info)
{
	t_redir	*redir;
	char	*expanded_value;

	redir = allocate_and_connect_redir(cmd, info);
	expanded_value = expand_value(token->next->value, info, cmd);
	if (has_delimiter(expanded_value) || \
(is_only_env(token->next->value) && !expanded_value[0]))
	{
		redir->type = REDIR_AMB;
		redir->file = token->next->value;
		cmd->is_error = 1;
		return (token->next);
	}
	if (token->type == IN)
		redir->type = REDIR_INPUT;
	else if (token->type == OUT)
		redir->type = REDIR_OUTPUT;
	else if (token->type == APPEND)
		redir->type = REDIR_APPEND;
	redir->file = expanded_value;
	return (token->next);
}

void	parser(t_info *info)
{
	t_token		*token;
	t_cmd		*cmd;

	token = info->tokens;
	(info->cmd_count)++;
	cmd = aalloc(&(info->arena), sizeof(t_cmd));
	if (!cmd)
		clean_and_exit("cmd");
	ft_memset(cmd, 0, sizeof(t_cmd));
	info->cmds = cmd;
	while (token)
	{
		if (token->type == PIPE)
			cmd = allocate_and_connect_cmd(cmd, info);
		else if (token->type == WORD)
			process_word_token(token, cmd, info);
		else if (token->type == HEREDOC)
			process_heredoc_token(token->next, cmd, info);
		else if (token->type == IN || token->type == OUT \
|| token->type == APPEND)
			token = process_redirection_token(token, cmd, info);
		token = token->next;
	}
}
