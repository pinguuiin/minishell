/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:32:41 by piyu              #+#    #+#             */
/*   Updated: 2025/06/20 04:24:24 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atocode(char *s)
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
 *non-numerical argument(s) - exit on 2 and *error message
 *numerical argument plus other arguments - code set to 1 and **error message
 * *error message:
 *@param argv
 */
int	shell_exit(char **argv)
{
	int	num;

	ft_putendl_fd("exit", STDOUT_FILENO); //not print / not exit in pipe?
	if (!argv[1])
		exit(0); //then how to check exit code? free data?
	num = ft_atocode(argv[1]);
	if (num >= 0 && !argv[2])
		exit(num);
	if (num < 0)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
	if (num >= 0 && argv[2])
	{
		ft_putendl_fd("exit: too many argument", STDERR_FILENO);
		return (1);
	}
	return (0);
}
