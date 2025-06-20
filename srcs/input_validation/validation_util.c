/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:55:59 by donheo            #+#    #+#             */
/*   Updated: 2025/06/20 17:09:19 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the  input contaions only whitespace characters
int	is_empty_input(const char *input)
{
	while (*input)
	{
		if (*input != ' ' || *input != '\t')
			return (0);
		input++;
	}
	return (1);
}
