/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:06:19 by donheo            #+#    #+#             */
/*   Updated: 2025/06/23 09:14:19 by donheo           ###   ########.fr       */
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

void	set_quote_and_word(int *quote_flag, t_cmd_type *cmd_type)
{
	*quote_flag = !(*quote_flag);
	cmd_type->has_word = 1;
}

int	skip_env_name(const char *input, t_cmd_type *cmd_type)
{
	(cmd_type->i)++;
	if (!(ft_isalpha(input[cmd_type->i]) || input[cmd_type->i] == '_'))
		return (cmd_type->i - 1);
	(cmd_type->i)++;
	while (input[cmd_type->i] && (ft_isalnum(input[cmd_type->i]) \
	|| input[cmd_type->i] == '_'))
		(cmd_type->i)++;
	cmd_type->has_env = 1;
	return (cmd_type->i - 1);
}

int	is_token_boundary(char c, t_cmd_type cmd_type)
{
	return (!((c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|') \
	&& !cmd_type.in_single_quote && !cmd_type.in_double_quote));
}
