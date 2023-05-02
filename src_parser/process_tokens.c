/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:33:04 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/02 17:51:32 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_home(t_token **current, char **env)
{
	char	*free_val;
	char	*value;
	char	*tmp;
	int		i;

	i = -1;
	if (!ft_strncmp((*current)->value, "~", ft_strlen((*current)->value)))
	{
		tmp = ft_getenv(env, "HOME");
		value = malloc(ft_strlen(tmp) + 1);
		while (tmp[++i])
			value[i] = tmp[i];
		value[i] = '\0';
		free_val = (*current)->value;
		(*current)->value = value;
		free(free_val);
	}
	else if (!ft_strncmp((*current)->value, "$?", 2))
	{
		tmp = ft_itoa(g_data->exit_status);
		value = malloc(ft_strlen(tmp) + 1);
		while (tmp[++i])
			value[i] = tmp[i];
		value[i] = '\0';
		free_val = (*current)->value;
		(*current)->value = value;
		free(free_val);
		free(tmp);
	}
	return (0);
}

char	*get_variable_value(char *s)
{
	int		len;
	char	*value;
	// char	*exit_status;
	char	*var_name;

	len = 1;
	var_name = s;
	while (ft_isalnum(s[len]) || s[len] == '_')
		len++;
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, s + 1, len + 1);
	var_name[len] = '\0';
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
			value = get_variable_value(tmp++);
			buf = ft_strjoin_gnl(buf, value);
			while (*tmp && (ft_isalnum(*tmp) || *tmp == '_' || *tmp == '?'))
				tmp++;
		}
		else
			ft_append_char(&buf, *tmp);
		if (*tmp)
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
	while (head && head->type == WORD)
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
		if (!ft_strncmp(head->value, "~", 1) || !ft_strncmp(head->value, "$?", 2))
			expand_home(&head, g_data->env);
		if (head->value)
			process_str(&head->value, &insq, &indq, buf);
		head = head->next;
	}
	return ;
}
