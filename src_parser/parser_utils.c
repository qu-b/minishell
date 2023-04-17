/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 17:59:52 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Double free for split
void	double_free(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

// Function to remove quotes from a string
char	*remove_quotes(char *s)
{
	int		len;
	char	*dest;
	char	*end;
	char	current_quote;

	len = ft_strlen(s);
	dest = s;
	end = s + len;
	current_quote = '\0';
	while (s < end)
	{
		if (current_quote == '\0' && (*s == '"' || *s == '\''))
		{
			current_quote = *s;
			s++;
		}
		else if (current_quote != '\0' && *s == current_quote)
		{
			current_quote = '\0';
			s++;
		}
		else
			*dest++ = *s++;
	}
	*dest = '\0';
	return (s);
}

// Function to expand an environment variable 
// such as $USER into its value (Marvin)
char	*expand_var(char *s)
{
	char	*variable;
	char	*value;
	int		len;
	int		var_len;
	char	*result;

	len = 1;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	var_len = len;
	while (s[len])
		len++;
	variable = (char *)malloc(var_len + 1);
	if (!variable)
		return (NULL);
	ft_strlcpy(variable, s + 1, var_len);
	variable[var_len] = '\0';
	value = ft_getenv(g_data->env, variable);
	free(variable);
	if (!value)
		return (NULL);
	result = malloc(ft_strlen(value) + ft_strlen(&s[var_len]) + 1);
	ft_strlcpy(result, value, ft_strlen(value) + 1);
	ft_strlcpy(result + ft_strlen(value),
		s + var_len, ft_strlen(&s[var_len]) + 1);
	return (result);
}

// Function to replace a variable with its value in a string
char	*replace_var(char *str)
{
	int		i;
	int		j;
	int		split_len;
	char	**split;
	char	*value;

	split = ft_split(str, ' ');
	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '$')
			{
				value = expand_var(split[i] + j);
				split[i] = ft_substr(split[i], 0, j);
				if (!value)
					break ;
				split[i] = ft_strjoin(split[i], value);
			}
		}
	}
	split_len = i;
	i = 0;
	ft_bzero(str, ft_strlen(str));
	while (split[i])
	{
		str = ft_strjoin(str, split[i]);
		if (i < split_len - 1)
			str = ft_strjoin(str, " ");
		i++;
	}
	double_free(split);
	return (str);
}

// Function that processes all tokens in the list,
// and removes quotes and expands variables. Still needs tweaking.
// Should ~ be expanded?
// yes, to ft_getenv(g_data->env, "HOME")
void	process_tokens(t_token *tokens)
{
	t_token	*head;
	int		in_sq;
	char	*p;

	head = tokens;
	while (head)
	{
		head->value = ft_strtrim(head->value, " ");
		if (head->value[0] == '\'')
		{
			remove_quotes(head->value);
			head->value = ft_strtrim(head->value, "\'");
		}
		else
		{
			in_sq = 0;
			p = head->value;
			while (*p)
			{
				if (*p == '\'')
					in_sq = !in_sq;
				else if (*p == '$' && !in_sq)
				{
					head->value = replace_var(head->value);
					head->value = ft_strtrim(head->value, "\"");
					break ;
				}
				p++;
			}
			if (!*p)
			{
				remove_quotes(head->value);
				head->value = ft_strtrim(head->value, "\"");
			}
		}
		head = head->next;
	}
}
