/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:33:04 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/26 19:23:11 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_variable_name(char *s)
{
	int		len;
	char	*variable;

	len = 1;
	if (!ft_strncmp(s, "$?", ft_strlen(s)))
		return ("?");
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	variable = (char *)malloc(len);
	if (!variable)
		return (NULL);
	ft_strlcpy(variable, s + 1, len);
	variable[len - 1] = '\0';
	return (variable);
}

char	*get_variable_value(char *variable)
{
	char	*value;

	if (!ft_strncmp(variable, "?", 1))
		return (ft_itoa(g_data->exit_status));
	else
		value = ft_getenv(g_data->env, variable);
	return (value);
}

char	*ft_append_char(char *str, char c)
{
	char	*result;

	result = (char *)malloc(ft_strlen(str) + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, ft_strlen(str));
	result[ft_strlen(str)] = c;
	result[ft_strlen(str) + 1] = '\0';
	return (result);
}

void	process_str(char **s, int *insq, int *indq, char *buf)
{
	char	*tmp;
	char	*value;

	tmp = *s;
	while (*tmp)
	{
		if (is_sq(*tmp) && !(*indq))
			*insq ^= 1;
		else if (is_dq(*tmp) && !(*insq))
			*indq ^= 1;
		else if (*tmp == '$' && (isalnum(*(tmp + 1))
				|| *(tmp + 1) == '?') && !(*insq))
		{
			value = get_variable_value(extract_variable_name(tmp));
			if (value)
				buf = ft_strjoin(buf, value);
			tmp += ft_strlen(extract_variable_name(tmp));
		}
		else
			buf = ft_append_char(buf, *tmp);
		tmp++;
	}
	free(*s);
	*s = buf;
}

void	process_tokens(t_token *head)
{
	int		insq;
	int		indq;
	char	*buf;

	insq = 0;
	indq = 0;
	buf = (char *)malloc(1);
	if (!buf)
		return ;
	while (head)
	{
		buf[0] = '\0';
		if (!ft_strncmp(head->value, "~", ft_strlen(head->value)))
			expand_home(&head, g_data->env);
		if (head->value)
			process_str(&head->value, &insq, &indq, buf);
		head = head->next;
	}
	free(buf);
}
