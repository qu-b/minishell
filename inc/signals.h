/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 07:29:31 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 10:02:04 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// doesn't behave exactly the same when running less or vim or other

# include "minishell.h"

// accept signals and launches appropriate functions depending on context
void	sig_acccept(void);
void	sig_handle(int sig);
void	sig_handle_ext(int sig);
void	sig_handle_in(int sig);

#endif
