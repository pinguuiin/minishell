/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:06:19 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 11:24:30 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *input, int i)
{
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (i);
}

void	append_token(t_token **head, t_token *tail)
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

t_token	*create_new_token(t_token_type type, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	if (!token)
		clean_and_exit("token allocation");
	token->type = type;
	token->value = NULL;
	return (token);
}

int	is_token_breaker(char c, int in_single_quote, int in_double_quote)
{
	return (!((c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|') \
&& !in_single_quote && !in_double_quote));
}
