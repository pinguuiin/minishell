/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:53:50 by donheo            #+#    #+#             */
/*   Updated: 2025/07/04 19:53:12 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_empty_string(const char *expanded_value, \
int in_single_quote, int in_double_quote)
{
	int	is_quote;

	is_quote = 0;
	while (*expanded_value)
	{
		if (*expanded_value == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			is_quote = 1;
		}
		else if (*expanded_value == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			is_quote = 1;
		}
		else if (*expanded_value == DELIMITER)
			;
		else
			return (0);
		expanded_value++;
	}
	if (is_quote)
		return (1);
	return (0);
}

char	*get_empty_string(t_info *info)
{
	char	*empty_str;

	empty_str = aalloc(&(info->arena), 2);
	if (!empty_str)
		clean_and_exit("empty string for word");
	empty_str[0] = 1;
	empty_str[1] = '\0';
	return (empty_str);
}


