/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:53:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 04:22:18 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_env_var(t_info *info, t_cmd *cmd)
{


}






void	parser(t_info *info)
{
	t_token		*token;
	t_cmd		*cmd;

	token = info->tokens;
	(info->num_cmds)++;
	cmd = aalloc(&(info->arena), sizeof(t_cmd));
	if (!cmd)
		clean_and_exit("memory allocation fails for cmd");
	info->cmds = cmd;
	while (token)
	{
		if (token->type == PIPE)
			cmd = alloc_and_connect_cmd(info, cmd);
		else if (token->type == ENV_VAR)
			save_env_var(info, cmd);
		else if (token->type == WORD)
			save_word(info, cmd);
		else if (token->type == WORD_WITH_ENV)
			save_word_with_env(info, cmd);
		else if (token->type == HEREDOC)
			token = save_heredoc(info, cmd, token);
		else
			token = save_redirections(info, cmd, token);
		token = token->next;
	}
}
