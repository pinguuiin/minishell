/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 03:33:45 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 01:09:41 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*allocate_and_connect_redir(t_info *info,t_cmd *cmd)
{
	t_redir	*new_redir;
	t_redir	*temp;

	if (!cmd->redirection)
	{
		cmd->redirection = aalloc(&(info->arena), sizeof(t_redir));
		if(!cmd->redirection)
			clean_and_exit("memory allocation fails for new cmd redir");
		new_redir = cmd->redirection;
	}
	else
	{
		temp = cmd->redirection;
		new_redir = aalloc(&(info->arena), sizeof(t_redir));
		if(!new_redir)
			clean_and_exit("memory allocation fails for cmd redir");
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
	return (new_redir);
}

static int	has_delimiter(const char *expanded_value)
{
	while (*expanded_value)
	{
		if (*expanded_value == 127)
			return (1);
		expanded_value++;
	}
	return (0);
}

int	is_ambiguous_redir(t_token *token, t_info *info)
{
	char	*expanded_value;

	expanded_value = expand_value(token->value, info);
	return (has_delimiter(expanded_value));
}
