/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:11:51 by donheo            #+#    #+#             */
/*   Updated: 2025/06/25 18:15:01 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*allocate_and_connect_cmd(t_info *info, t_cmd *cmd)
{
	t_cmd	*new_cmd;

	(info->num_cmds)++;
	new_cmd = aalloc(&(info->arena), sizeof(t_cmd));
	if (!new_cmd)
		clean_and_exit("memory allocation fails for new cmd");
	cmd->next = new_cmd;
	return (new_cmd);
}

t_redir	*allocate_and_connect_redir(t_info *info,t_cmd *cmd)
{
	t_redir	*new_redir;
	t_redir	*temp;
	if (!cmd->redirection)
	{
		cmd->redirection = alloc(&(info->arena), sizeof(t_redir));
		if(!cmd->redirection)
			clean_and_exit("memory allocation fails for new cmd redir");
		new_redir = cmd->redirection;
	}
	else
	{
		temp = cmd->redirection;
		new_redir = alloc(&(info->arena), sizeof(t_redir));
		if(!new_redir)
			clean_and_exit("memory allocation fails for cmd redir");
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
	return (new_redir);
}


