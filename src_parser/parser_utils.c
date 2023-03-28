/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 19:48:52 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to remove quotes from a string
char *remove_quotes(char *s)
{
	int		i;
	char	*value;

	i = 1;
	while (s[i] != '\'' && s[i] != '\"' && s[i])
		i++;
	value = malloc(i + 1);
	ft_strlcpy(value, s + 1, i);
	value[i] = '\0';
	free(s);
	return (value);
}

// Function to expand an environment variable such as $USER
char *expand_var(const char *s)
{
	char *value;
	char *result;
	char *start;
	size_t len;

	start = ft_strchr(s, '$');
	if (!start)
		return (NULL);

	len = 0;
	// Fix this loop with ft_isalnum & str == '_'
	while (*start != '\0' && *start != '\"' && *start != '=')
	{
		start++;
		len++;
	}
	value = (char *) malloc(len + 1);
	ft_strlcpy(value, s + 1, len);
	value[len] = '\0';
	result = getenv(value);
	free(value);
	return (result);
}

// Function to replace a variable with its value
char *replace_var(const char *variable, int var_start, const char *value)
{
	size_t	value_len;
	size_t	variable_len;
	char	*new_value;

	value_len = ft_strlen(value);
	variable_len = ft_strlen(variable);
	new_value = (char *)malloc(value_len + 1);
	ft_memcpy(new_value, variable, var_start);
	ft_memcpy(new_value + var_start, value, value_len);
	new_value[value_len] = '\0';
	return (new_value);
}

// Function that processes all tokens in the list,
//  and removes quotes and expands variables. Might still need tweaking.
// Should ~ be expanded?
void process_tokens(t_token *tokens)
{
	int		i;
	char	*expanded;
	char	*new_val;
	t_token	*head;

	i = 0;
	head = tokens;
	while (head)
	{
		if (head->value[0] == '\'')
			head->value = remove_quotes(head->value);
		else if (head->value[0] == '\"')
		{
			while (head->value[i])
			{
				if (head->value[i] == '$')
				{
					expanded = expand_var(head->value + i);
					if (expanded)
					{
						new_val = replace_var(head->value, i - 1, expanded);
						// free(expanded);
						free(head->value);
						head->value = new_val;
					}
					else
						i++;
				}
				i++;
			}
		}
		head = head->next;
	}
}
