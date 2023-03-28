/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 17:03:46 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_variable_char(char c)
{
	return (isalnum(c) || c == '_');
}

char *expand_variable(char *input)
{
	char	*end = input;
	char *name;
	char *value;

	while (*end && is_valid_variable_char(*end))
		end++;
	name = strndup(input, end - input);
	if (!name)
		return NULL;
	value = getenv(name);
	free(name);
	return value ? strdup(value) : NULL;
}
