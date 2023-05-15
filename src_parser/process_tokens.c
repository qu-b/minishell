/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:33:04 by zaphod           #+#    #+#             */
/*   Updated: 2023/05/12 10:59:25 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_variable(char **tmp, char **buf)
{
	char	*value;
	char	*variable;
	char	*vtmp;
	int		i;

	i = 0;
	variable = malloc(ft_strlen(*tmp));
	if (!variable)
		return ;
	(*tmp)++;
	vtmp = *tmp;
	while (ft_isalnum(vtmp[i]) || vtmp[i] == '_')
	{
		variable[i] = vtmp[i];
		i++;
	}
	variable[i] = '\0';
	value = get_variable_value(variable);
	if (value)
		*buf = ft_strjoin_gnl(*buf, value);
	while (**tmp && (ft_isalnum(**tmp) || **tmp == '_'))
		(*tmp)++;
	(*tmp)--;
	free(value);
	free(variable);
}

void	handle_exit(char **tmp, char **buf)
{
	char	*value;

	value = get_variable_value(*tmp);
	(*tmp)++;
	if (value)
		*buf = ft_strjoin_gnl(*buf, value);
	free(value);
}

void	process_str(char **s, int *insq, int *indq, char *buf)
{
	char	*tmp;

	tmp = *s;
	while (*tmp)
	{
		if (is_sq(*tmp) && !(*indq))
			*insq ^= 1;
		else if (is_dq(*tmp) && !(*insq))
			*indq ^= 1;
		else if (is_variable(tmp) && !(*insq))
			handle_variable(&tmp, &buf);
		else if (!ft_strncmp(tmp, "$?", 2) && !(*insq))
			handle_exit(&tmp, &buf);
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
	while (head && head->value[0] && head->type == WORD)
	{
		buf = (char *)malloc(str_length(head->value) + 1);
		if (!buf)
			return ;
		ft_bzero(buf, str_length(head->value));
		if (!ft_strncmp(head->value, "~", 1))
			expand_home(&head, g_data->env);
		if (head->value)
			process_str(&head->value, &insq, &indq, buf);
		head = head->next;
	}
	return ;
}
