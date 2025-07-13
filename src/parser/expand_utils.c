/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:20:02 by donheo            #+#    #+#             */
/*   Updated: 2025/07/13 09:54:57 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_exit_code(char *expanded, int *i, int *j)
{
	char	*exit_str;
	int		k;
	t_info	*info;

	info = get_info();
	exit_str = ft_arena_itoa(info->exit_code);
	k = 0;
	while (exit_str[k])
		expanded[(*j)++] = exit_str[k++];
	*i += 2;
}

void	remove_delimiter(char *expanded_value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (expanded_value[i] == DELIMITER)
		i++;
	while (expanded_value[i])
	{
		if (expanded_value[i] == DELIMITER)
		{
			expanded_value[j++] = expanded_value[i++];
			while (expanded_value[i] == DELIMITER)
				i++;
			continue ;
		}
		expanded_value[j++] = expanded_value[i++];
	}
	if (j > 0 && expanded_value[j - 1] == DELIMITER)
		expanded_value[j - 1] = '\0';
	else
		expanded_value[j] = '\0';
}

int	itoa_len(int n)
{
	long	num;
	int		len;

	num = n;
	if (num == 0)
		return (1);
	len = 0;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	convert(int n, char *str, int len)
{
	long	num;

	str[len] = '\0';
	num = n;
	if (num < 0)
	{
		str[0] = '-';
		num *= (-1);
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_arena_itoa(int n)
{
	int		len;
	char	*str;
	t_info	*info;

	info = get_info();
	len = itoa_len(n);
	str = aalloc(&(info->arena), len + 1);
	if (!str)
		return (NULL);
	convert(n, str, len);
	return (str);
}
