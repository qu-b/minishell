/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:33:04 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/28 13:25:21 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_home(t_token **current, char **env)
{
	if ((*current)->value[0] == '~')
		(*current)->value = ft_getenv(env, "HOME");
	return (0);
}

char	*get_variable_value(char *s)
{
	int		len;
	char	*value;
	char	*exit_status;
	char	*var_name;

	len = 1;
	var_name = s;
	if (!ft_strncmp(s, "$?", ft_strlen(s)))
	{
		exit_status = ft_itoa(g_data->exit_status);
		value = exit_status;
		free(exit_status);
		return (value);
	}
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	var_name = (char *)malloc(len);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, s + 1, len);
	var_name[len - 1] = '\0';
	value = ft_getenv(g_data->env, var_name);
	free(var_name);
	return (value);
}

void	ft_append_char(char **buf, char tmp)
{
	char	res[2];

	res[0] = tmp;
	res[1] = '\0';
	*buf = ft_strjoin_gnl(*buf, res);
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
			value = get_variable_value(tmp);
			if (value)
				buf = ft_strjoin_gnl(buf, value);
			tmp += ft_strlen(tmp) - 1;
		}
		else
			ft_append_char(&buf, *tmp);
		tmp++;
	}
	free(*s);
	*s = buf;
	return ;
}

void	process_tokens(t_token *head)
{
	int		insq;
	int		indq;
	char	*buf;

	insq = 0;
	indq = 0;
	while (head)
	{
		if (head->type == WORD)
			buf = (char *)malloc(str_length(head->value) + 1);
		else
			buf = (char *)(malloc(ft_strlen(head->value)) + 1);
		if (!buf)
			return ;
		if (head->type == WORD)
			ft_bzero(buf, str_length(head->value));
		else
			ft_bzero(buf, ft_strlen(head->value));
		if (!ft_strncmp(head->value, "~", ft_strlen(head->value)))
			expand_home(&head, g_data->env);
		if (head->value)
			process_str(&head->value, &insq, &indq, buf);
		head = head->next;
	}
}
