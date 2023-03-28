/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:38:33 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 11:50:56 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	quote_handler(char *input, int quote)
// {
// 	int	i;
// 	int	dquote_count;
// 	int	squote_count;

// 	i = 1;
// 	while (input[i])
// 	{
// 		if (quote == 2)
// 		{

// 		}
// 	}
// }

// t_token	*lexer(char *input)
// {
// 	int		n;
// 	t_token	*tokens;

// 	n = -1;
// 	while (*input && n < ft_strlen(input) + 1)
// 	{
// 		if (*input == '\0' )
// 			break ;
// 		while (is_space(*input))
// 			input++;
// 		if (is_io(input) > 0)
// 			tokens[n++] = *create_token(IO, &input, is_io(input));
// 		else if (is_pipe(*input))
// 			tokens[n++] = *create_token(PIPE, &input, 1);
// 		else if (ft_isalpha(*input))
// 			tokens[n++] = *create_token(CMD, &input, word_length(input));
// 		else if (*input == '-')
// 			tokens[n++] = *create_token(ARG, &input, word_length(input));
// 		else if (*input == '\'' || *input == '\"')
// 			tokens[n++] = *tokenize_string(&input);
// 		else if (*input == '$')
// 			tokens[n++] = *create_token(VAR, (&input), word_length(input));
// 		else if (*input == '/')
// 			tokens[n++] = *create_token(PATH, &input, word_length(input));
// 	}
// 	tokens[n].value = NULL;
// 	return (tokens);
// }


// t_token	*ftlexer(char *input)
// {
// 	int		n;
// 	int		len;
// 	t_token	*tokens;

// 	n = 0;
// 	len = ft_strlen(input);
// 	tokens = malloc(sizeof(t_token) * (len + 1));
// 	if (!tokens)
// 		return (NULL);
// 	while (input && n < len)
// 	{
// 		if (*input == '\0' )
// 			break ;
// 		// Skip whitespace
// 		while (is_space(*input))
// 			input++;
// 		// Tokenize IO + pipe
// 		if (is_io(input) > 0)
// 		{
// 			tokens[n] = *create_token(IO, &input, is_io(input));
// 			n++;
// 		}
// 		else if (is_pipe(*input))
// 		{
// 			tokens[n] = *create_token(PIPE, &input, 1);
// 			n++;
// 		}
// 		// Tokenize Commands, Args and String
// 		else if (ft_isalpha(*input) || *input == '-' || *input == '\'' || *input == '\"')
// 		{
// 			if (*input == '-')
// 				tokens[n] = *create_token(ARG, &input, word_length(input));
// 			else if (*input == '\'' || *input == '\"')
// 				tokens[n] = *tokenize_string(&input);
// 			else
// 				tokens[n] = *create_token(CMD, &input, word_length(input));
// 			n++;
// 		}
// 		// Tokenize Environment variable
// 		else if (*input == '$')
// 		{
// 			input++;
// 			tokens[n] = *create_token(VAR, (&input), word_length(input));
// 			n++;
// 		}
// 		// Tokenize Path
// 		else if (*input == '/')
// 		{
// 			tokens[n] = *create_token(PATH, &input, word_length(input));
// 			n++;
// 		}
// 		else
// 			input++;
// 	}
// 	tokens[n].value = NULL;
// 	return (tokens);
// }
