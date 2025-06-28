/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:06:19 by donheo            #+#    #+#             */
/*   Updated: 2025/06/28 21:19:05 by donheo           ###   ########.fr       */
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

int	is_token_boundary(char c, int in_single_quote, int in_double_quote)
{
	return (!((c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|') \
	&& !in_single_quote && !in_double_quote));
}
