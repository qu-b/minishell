/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 07:29:31 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/11 00:45:35 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

// accepts signals and launches appropriate functions depending on context
void	sig_acccept(void);

// signal actions for SIGINT and SIGQUIT, whether ext or int bin is being run
void	sig_handle(int sig);

// disables display of control characters
void	show_ctrl_disable(void);

// enables display of control characters
void	show_ctrl_enable(void);

#endif
