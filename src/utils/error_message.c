/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:12:12 by donheo            #+#    #+#             */
/*   Updated: 2025/07/16 16:02:56 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	caluclate_message_len(char *s1, \
char *s2, char *s3, const char *err)
{
	size_t	len;

	len = ft_strlen(s3) + 1;
	if (s1)
		len += ft_strlen(s1) + 2;
	if (s2)
		len += ft_strlen(s2) + 2;
	else
		len += ft_strlen(err) + 2;
	return (len + 1);
}

static void	append_str(char **dst, char *src)
{
	while (*src)
		*(*dst)++ = *src++;
}

static void	append_with_sep(char **dst, char *s1, char *s2)
{
	append_str(dst, s1);
	*(*dst)++ = ':';
	*(*dst)++ = ' ';
	append_str(dst, s2);
}

int	error_msg(char *s1, char *s2, char *s3, int exit_code)
{
	char		*buffer;
	char		*ptr;
	size_t		len;
	const char	*err;

	get_info()->exit_code = exit_code;
	err = strerror(errno);
	len = caluclate_message_len(s1, s2, s3, err);
	buffer = aalloc(&(get_info()->arena), len);
	if (!buffer)
		clean_and_exit("error message buffer");
	ptr = buffer;
	if (s1)
		append_with_sep(&ptr, s1, "");
	if (s2)
		append_with_sep(&ptr, s2, s3);
	else
		append_with_sep(&ptr, s3, (char *)err);
	*ptr++ = '\n';
	write(STDERR_FILENO, buffer, ptr - buffer);
	return (exit_code);
}
