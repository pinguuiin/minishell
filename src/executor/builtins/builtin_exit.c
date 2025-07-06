/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:32:41 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 00:38:03 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_atocode(char *s)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (!s || !*s)
		return (-1);
	if (*s == '+' || *s == '-')
	{
		sign = 44 - *s;
		s++;
	}
	if (*s < '0' || *s > '9')
		return (-1);
	while (*s >= '0' && *s <= '9')
	{
		if (num > 9223372036854775807.0 / 10.0 + ('0' - *s) / 10.0)
			return (-1);
		num = num * 10 + *s - '0';
		s++;
	}
	if (*s)
		return (-1);
	return ((unsigned long long)(num * sign) % 256);
}

/*exit current shell with the exit code given as argument (optional)
 *no argument - exit on 0
 *one numerical argument - exit on (unsigned int)arg % 256
 						- exceeding long long treated as a string
 *non-numerical argument(s) - exit on 2 and *error message
 *numerical argument plus other arguments - code set to 1 and **error message
 * *error message:
 *@param argv
 */
int	shell_exit(t_info *info, char **argv)
{
	int	num;

	if (info->cmd_count == 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!argv[1])
		silent_exit(0);
	num = ft_atocode(argv[1]);
	if (num >= 0 && !argv[2])
		silent_exit(num);
	if (num < 0)
		exec_exit("minishell: exit", argv[1], "numeric argument required", 2);
	if (num >= 0 && argv[2])
		return (error_msg("minishell", "exit", "too many argument", 1));
	return (1);
}
