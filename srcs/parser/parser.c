/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:53:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 02:23:35 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_cmd(t_info *info, t_cmd *cmd, t_token *token)
{
	char	*expanded_value;
	char	**divided_value;
	int		i;

	expanded_value = expand_value(token->value, info);
	divided_value = divide_by_delimiter(expanded_value, info);
	i = 0;
	while (divided_value[i])
	{
		add_to_argv(cmd, divided_value[i++], info);
	}
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
		else if (token->type == WORD || token->type == ENV_VAR || token->type == WORD_WITH_ENV)
			save_cmd(info, cmd, token);
		else if (token->type == HEREDOC)
			token = save_heredoc(info, cmd, token);
		else
			token = save_redirection(info, cmd, token);
		token = token->next;
	}
}
