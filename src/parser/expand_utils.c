/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:20:02 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 21:00:49 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
