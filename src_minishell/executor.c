/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/30 16:04:12 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse_cmd(t_token *tokens)
// {
// 	t_token	*head;

// 	head = tokens;
// 	while (head)
// 	{
// 		if (head->type == IO)
// 		{
// 			head = head->next;
// 			if (access(head->value, F_OK) || access(head->value, R_OK))
// 			{
// 				perror("File Existence or Permission Error");
// 				return (1);
// 			}
// 		}
// 		else

// 		head->next;
// 	}
// 	return (0);
// }

char **get_args(t_token *token)
{
	char **args = malloc(sizeof(char *));
	int i = 0;
	while (token != NULL && token->type != PIPE && token->type != IO)
	{
		args[i++] = token->value;
		args = realloc(args, sizeof(char *) * (i + 1));
		token = token->next;
	}
	args[i] = NULL;
	return args;
}

void executor(t_token *tokens, char **envp)
{
	int fdin = STDIN_FILENO;
	int fdout = STDOUT_FILENO;
	int pipefd[2];
	int status;
	pid_t pid;

	while (tokens != NULL)
	{
		if (tokens->type == IO)
		{
			if (tokens->value[0] == '<')
			{
				// Input redirection
				fdin = open(tokens->next->value, O_RDONLY);
				if (fdin == -1)
				{
					perror("Error");
					return;
				}
			}
			else
			{
				// Output redirection
				fdout = open(tokens->next->value, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				if (fdout == -1) {
					perror("Error");
					return;
				}
			}
			tokens = tokens->next;
		}
		else if (tokens->type == PIPE)
		{
			// Create pipe
			if (pipe(pipefd) == -1)
			{
				perror("Error");
				return;
			}

			// Fork child process
			pid = fork();
			if (pid == -1)
			{
				perror("Error");
				return;
			}
			else if (pid == 0)
			{
				// Child process: redirect output to pipe
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				if (fdin != STDIN_FILENO)
				{
					dup2(fdin, STDIN_FILENO);
					close(fdin);
				}
				execvp(tokens->next->value, &tokens->next->value);
				perror("Error");
				return;
			}
			else
			{
				// Parent process: receive input from pipe
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(fdin);
				waitpid(pid, &status, 0);
				if (WEXITSTATUS(status) != 0)
				{
					perror("Error");
					return;
				}
				fdin = pipefd[0];
				tokens = tokens->next->next;
			}
		}
		else
		{
			// Execute command
			char *command = get_cmd(ft_split(find_path(envp), ':'), tokens->value);
			char **args = get_args(tokens);
			if (fdin != STDIN_FILENO)
			{
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			if (fdout != STDOUT_FILENO)
			{
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
			execve(command, args, envp);
			perror("Error");
			return;
		}
	}
}
