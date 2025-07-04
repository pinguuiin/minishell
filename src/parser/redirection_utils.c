/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 03:33:45 by donheo            #+#    #+#             */
/*   Updated: 2025/07/04 10:36:49 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*allocate_and_connect_redir(t_cmd *cmd, t_info *info)
{
	t_redir	*new_redir;
	t_redir	*temp;

	if (!cmd->redirection)
	{
		cmd->redirection = aalloc(&(info->arena), sizeof(t_redir));
		if (!cmd->redirection)
			clean_and_exit("new cmd redir");
		new_redir = cmd->redirection;
	}
	else
	{
		temp = cmd->redirection;
		new_redir = aalloc(&(info->arena), sizeof(t_redir));
		if (!new_redir)
			clean_and_exit("cmd redir");
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
	new_redir->fd = -1;
	return (new_redir);
}

int	has_delimiter(const char *expanded_value)
{
	while (*expanded_value)
	{
		if (*expanded_value == DELIMITER)
			return (1);
		expanded_value++;
	}
	return (0);
}

int	is_quoted_heredoc(const char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
