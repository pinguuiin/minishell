/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:20:02 by donheo            #+#    #+#             */
/*   Updated: 2025/07/07 11:35:12 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	calculate_env_len(const char *value, int *i, int *value_len)
{
	int		key_len;
	t_info	*info;
	t_env	*env_list;

	key_len = 1;
	info = get_info();
	env_list = find_env_by_name(value, *i, info);
	if (!env_list || !env_list->value)
		return ;
	else
		*value_len += ft_strlen(env_list->value);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
}

void	save_env_value_with_del(const char *value, char *expanded, \
int *i, int *j)
{
	t_env	*env_list;
	int		k;
	t_info	*info;

	k = 0;
	info = get_info();
	env_list = find_env_by_name(value, *i, info);
	while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
		(*i)++;
	if (!env_list || !env_list->value)
		return ;
	while ((env_list->value)[k])
	{
		if ((env_list->value)[k] == ' ' || (env_list->value)[k] == '\t')
		{
			expanded[(*j)++] = DELIMITER;
			k = skip_spaces(env_list->value, k);
			continue ;
		}
		expanded[(*j)++] = (env_list->value)[k++];
	}
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
