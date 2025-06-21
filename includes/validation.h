/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:18:49 by donheo            #+#    #+#             */
/*   Updated: 2025/06/21 19:11:37 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

int		is_empty_input(const char *input);
int		validate_quotes(const char *cmd);
int		validate_redirections(const char *cmd);
int		validate_operations(const char *cmd, int expect_command);
int		check_syntax_error(const char *cmd);
int		is_heredoc_limit_exceeded(const char *input);

#endif
