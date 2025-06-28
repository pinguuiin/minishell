/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:18:49 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 02:05:41 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

int		is_only_spaces(const char *input);
int		validate_quotes(const char *cmd);
int		check_syntax_error(const char *cmd);

#endif
