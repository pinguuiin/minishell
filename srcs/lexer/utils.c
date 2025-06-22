/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:06:19 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 15:42:42 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

void	connect_tokens(t_token **head, t_token *tail)
{
	t_token	*current;

	tail->next = NULL;
	if (*head == NULL)
	{
		*head = tail;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = tail;
}
