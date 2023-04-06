/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 06:57:11 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int		i;
	char	*value;

	i = 1;
	if (s[0] != '\'' && s[0] != '\"')
		return (s);
	while (s[i] != '\'' && s[i] != '\"' && s[i])
		i++;
	value = malloc(i + 1);
	ft_strlcpy(value, s + 1, i);
	value[i] = '\0';
	free(s);
	return (value);
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
	if (!value)
		return (NULL);
	free(variable);
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
	int		split_len;
	char	**split;

	split = ft_split(str, ' '); 
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$') //envars can appear in between non space characters
			split[i] = expand_var(split[i]);
		i++;
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
void	process_tokens(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (head)
	{
		if (head->value[0] == '\"')
		{
			head->value = remove_quotes(head->value);
			head->value = replace_var(head->value);
		}
		if (head->value[0] == '\'')
			head->value = remove_quotes(head->value);
		else // envars need to be replaced even when they are not in double quotes
			head->value = replace_var(head->value);
		head = head->next;
	}
}
