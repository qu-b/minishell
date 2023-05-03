/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 07:51:13 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/03 07:52:00 by fcullen          ###   ########.fr       */
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
	return (0);
}

char	*get_variable_value(char *s)
{
	int		len;
	char	*value;
	char	*var_name;

	len = 1;
	var_name = s;
	if (!ft_strncmp(s, "$?", 2))
	{
		value = ft_itoa(g_data->exit_status);
		return (value);
	}
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
