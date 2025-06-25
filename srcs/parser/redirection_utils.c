/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 03:33:45 by donheo            #+#    #+#             */
/*   Updated: 2025/06/26 00:55:23 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
